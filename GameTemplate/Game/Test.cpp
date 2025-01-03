using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

/// <summary>
/// プレイヤーのロックオン機能の制御するクラス
/// </summary>
public class PlayerLockon : MonoBehaviour
{
    [SerializeField] PlayerCamera playerCamera;
    [SerializeField] Transform originTrn;
    [SerializeField] float lockonRange = 20;
    [SerializeField] LayerMask lockonLayers = 0;
    [SerializeField] LayerMask lockonObstacleLayers = 0;
    [SerializeField] GameObject lockonCursor;

    float lockonFactor = 0.3f;
    float lockonThreshold = 0.5f;
    bool lockonInput = false;
    public bool isLockon = false;

    Camera mainCamera;
    Transform cameraTrn;
    GameObject targetObj;

    void Start()
    {
        mainCamera = Camera.main;
        cameraTrn = mainCamera.transform;
    }

    void Update()
    {
        if (lockonInput)
        {
            //Debug.Log("isLockon: " + isLockon);
            // すでにロックオン済みなら解除する
            if (isLockon)
            {
                isLockon = false;
                lockonCursor.SetActive(false);
                lockonInput = false;
                playerCamera.InactiveLockonCamera();
                targetObj = null;
                return;
            }

            // ロックオン対象の検索、いるならロックオン、いないならカメラ角度をリセット
            targetObj = GetLockonTarget();
            //Debug.Log("tagetObj: " + targetObj);
            if (targetObj)
            {
                isLockon = true;
                playerCamera.ActiveLockonCamera(targetObj);
                lockonCursor.SetActive(true);
            }
            else
            {
                playerCamera.ResetFreeLookCamera();
            }
            lockonInput = false;
        }

        // ロックオンカーソル
        if (isLockon)
        {
            lockonCursor.transform.position = mainCamera.WorldToScreenPoint(targetObj.transform.position);
            float lookAtDistance = Vector3.Distance(playerCamera.GetLookAtTransform().position, originTrn.position);
            if (lookAtDistance > lockonRange)
            {
                isLockon = false;
                lockonCursor.SetActive(false);
                lockonInput = false;
                playerCamera.InactiveLockonCamera();
                targetObj = null;
                return;
            }
        }
    }

    public void OnLockon(InputAction.CallbackContext context)
    {
        switch (context.phase)
        {
        case InputActionPhase.Performed:
            // ボタンが押された時の処理
            lockonInput = true;
            //Debug.Log("lockonInput: " + lockonInput);
            break;

        case InputActionPhase.Canceled:
            // ボタンが離された時の処理
            break;
        }
    }

    /// <summary>
    /// ロックオン対象の計算処理を行い取得する
    /// 計算は3つの工程に分かれる
    /// </summary>
    /// <returns></returns>
    GameObject GetLockonTarget()
    {
        // 1. SphereCastAllを使ってPlayer周辺のEnemyを取得しListに格納
        RaycastHit[] hits = Physics.SphereCastAll(originTrn.position, lockonRange, Vector3.up, 0, lockonLayers);

        if (hits ? .Length == 0)
        {
            // 範囲内にターゲットなし
            return null;
        }

        // 2. 1のリスト全てにrayを飛ばし射線が通るものだけをList化
        List<GameObject> hitObjects = makeListRaycastHit(hits);
        if (hitObjects ? .Count == 0)
        {
            // 射線が通ったターゲットなし
            return null;
        }

        // 3. 2のリスト全てのベクトルとカメラのベクトルを比較し、画面中央に一番近いものを探す
        var tumpleData = GetOptimalEnemy(hitObjects);

        float degreemum = tumpleData.Item1;
        GameObject target = tumpleData.Item2;

        //// 求めた一番小さい値が一定値より小さい場合、ターゲッティングをオンにします
        if (Mathf.Abs(degreemum) <= lockonThreshold)
        {
            return target;
        }
        return null;
    }

    bool frag = true;
    public void OnCameraXY(InputAction.CallbackContext context)
    {
        var inputValue = context.ReadValue<Vector2>();
        if (isLockon)
        {
            if (frag)
            {
                if (inputValue.x > 0.95f)
                {
                    Debug.Log("right: " + inputValue.x);
                    frag = false;
                    GameObject rightEnemy = GetLockonTargetLeftOrRight("right");
                    if (rightEnemy != null)
                    {
                        targetObj = rightEnemy;
                        playerCamera.ActiveLockonCamera(targetObj);
                        lockonCursor.SetActive(true);
                    }

                }
                else if (inputValue.x < -0.95f)
                {
                    Debug.Log("left: " + inputValue.x);
                    frag = false;
                    GameObject leftEnemy = GetLockonTargetLeftOrRight("left");
                    if (leftEnemy != null)
                    {
                        targetObj = leftEnemy;
                        playerCamera.ActiveLockonCamera(targetObj);
                        lockonCursor.SetActive(true);
                    }
                }
            }
        }
        if (context.canceled)
        {
            frag = true;
        }
    }

    // 2. 1のリスト全てにrayを飛ばし射線が通るものだけをList化
    // Raycastの発射位置によっては自モデルに当たって遮蔽物扱いされる場合がある
    private List<GameObject> makeListRaycastHit(RaycastHit[] hits)
    {
        List<GameObject> hitObjects = new List<GameObject>();
        RaycastHit hit;
        for (var i = 0; i < hits.Length; i++)
        {
            var direction = hits[i].collider.gameObject.transform.position - (originTrn.position);

            if (Physics.Raycast(originTrn.position, direction, out hit, lockonRange, lockonObstacleLayers))
            {
                if (hit.collider.gameObject == hits[i].collider.gameObject)
                {
                    hitObjects.Add(hit.collider.gameObject);
                }
            }
            //Debug.DrawRay(originTrn.position, direction * lockonRange, Color.red);
        }
        return hitObjects;
    }

    // 3. 2のリスト全てのベクトルとカメラのベクトルを比較し、画面中央に一番近いものを探す
    // degreep: カメラの前方ベクトルX,Z成分からなる角度
    private (float, GameObject) GetOptimalEnemy(List<GameObject> hitObjects)
    {
        float degreep = Mathf.Atan2(cameraTrn.forward.x, cameraTrn.forward.z);
        float degreemum = Mathf.PI * 2;
        GameObject target = null;

        foreach(var enemy in hitObjects)
        {
            // pos: 敵からカメラへ向けたベクトル
            // pos2: カメラから敵に向けたベクトル(水平方向に制限して正規化)
            Vector3 pos = cameraTrn.position - enemy.transform.position;
            Vector3 pos2 = enemy.transform.position - cameraTrn.position;
            pos2.y = 0.0f;
            pos2.Normalize();

            // degree: pos2のX,Z成分からなる角度. カメラの前方からどれだけ回転しているか
            float degree = Mathf.Atan2(pos2.x, pos2.z);
            // degreeを-180°〜180°に正規化
            degree = degreeNormalize(degree, degreep);

            // pos.magnitude: 敵とカメラの距離
            // pos.magnitudeに応じて角度に重みをかけ、距離が近いほど角度の重みが大きく選好される
            degree = degree + degree * (pos.magnitude / 500) * lockonFactor;
            // Mathf.Abs(degreemum): 以前に記録された最小角度差の絶対値
            // Mathf.Abs(degree): 現在の角度差の絶対値
            if (Mathf.Abs(degreemum) >= Mathf.Abs(degree))
            {
                degreemum = degree;
                target = enemy;
            }
        }
        return (degreemum, target);
    }

    // degreeを-180°〜180°に正規化
    private float degreeNormalize(float degree, float degreep)
    {
        if (Mathf.PI <= (degreep - degree))
        {
            // degreep (カメラの前方ベクトル) とdegree (カメラから敵へのベクトル) との角度差が180°以上
            // degreeから360°引いて正規化(-180から180に制限)
            degree = degreep - degree - Mathf.PI * 2;
        }
        else if (-Mathf.PI >= (degreep - degree))
        {
            // degreep (カメラの前方ベクトル) とdegree (カメラから敵へのベクトル) との角度差が-180°以下
            // degreeから360°足して正規化(-180から180に制限)
            degree = degreep - degree + Mathf.PI * 2;
        }
        else
        {
            // そのままdegreeを使用
            degree = degreep - degree;
        }
        return degree;
    }

    // マウス、右スティック入力時の処理
    private GameObject GetLockonTargetLeftOrRight(string direction)
    {
        float degreemum;
        GameObject target;
        //GameObject current = null;
        // 1. SphereCastAllを使ってPlayer周辺のEnemyを取得しListに格納
        RaycastHit[] hits = Physics.SphereCastAll(originTrn.position, lockonRange, Vector3.up, 0, lockonLayers);
        // 2. 1のリスト全てにrayを飛ばし射線が通るものだけをList化
        List<GameObject> hitObjects = makeListRaycastHit(hits);
        // 3. 2のリスト全てのベクトルとカメラのベクトルを比較し、画面中央に一番近いものを探す
        if (direction.Equals("left"))
        {
            // 左入力時
            var tumpleData = GetEnemyLeftOrRight(hitObjects, "left");
            degreemum = tumpleData.Item1;
            target = tumpleData.Item2;
        }
        else
        {
            // 右入力時
            var tumpleData = GetEnemyLeftOrRight(hitObjects, "right");
            degreemum = tumpleData.Item1;
            target = tumpleData.Item2;
        }
        return target;
    }

    private (float, GameObject) GetEnemyLeftOrRight(List<GameObject> hitObjects, string direction)
    {
        float degreep = Mathf.Atan2(cameraTrn.forward.x, cameraTrn.forward.z);
        float degreemum = Mathf.PI * 2;
        GameObject target = null;
        //Vector3 currentLookAt = playerCamera.GetLookAtPosition();

        foreach(var enemy in hitObjects)
        {
            if (enemy == targetObj)
            {
                continue;
            }
            // pos: 敵からカメラへ向けたベクトル
            // pos2: カメラから敵に向けたベクトル(水平方向に制限して正規化)
            Vector3 pos = cameraTrn.position - enemy.transform.position;
            Vector3 pos2 = enemy.transform.position - cameraTrn.position;
            pos2.y = 0.0f;
            pos2.Normalize();

            // degree: pos2のX,Z成分からなる角度. カメラの前方からどれだけ回転しているか
            float degree = Mathf.Atan2(pos2.x, pos2.z);
            // degreeを-180°〜180°に正規化
            degree = degreeNormalize(degree, degreep);
            if (direction.Equals("left"))
            {
                if (degree < 0)
                {
                    // enemyが画面中央より右側にいる場合候補から外す
                    continue;
                }
            }
            else
            {
                if (degree > 0)
                {
                    // enemyが画面中央より左側にいる場合候補から外す
                    continue;
                }
            }
            // pos.magnitude: 敵とカメラの距離
            // pos.magnitudeに応じて角度に重みをかけ、距離が近いほど角度の重みが大きく選好される
            degree = degree + degree * (pos.magnitude / 500) * lockonFactor;
            // Mathf.Abs(degreemum): 以前に記録された最小角度差の絶対値
            // Mathf.Abs(degree): 現在の角度差の絶対値
            if (Mathf.Abs(degreemum) >= Mathf.Abs(degree))
            {
                degreemum = degree;
                target = enemy;
            }
        }
        return (degreemum, target);
    }

    public Transform GetLockonCameraLookAtTransform()
    {
        return playerCamera.GetLookAtTransform();
    }
}