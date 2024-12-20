using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

/// <summary>
/// �v���C���[�̃��b�N�I���@�\�̐��䂷��N���X
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
            // ���łɃ��b�N�I���ς݂Ȃ��������
            if (isLockon)
            {
                isLockon = false;
                lockonCursor.SetActive(false);
                lockonInput = false;
                playerCamera.InactiveLockonCamera();
                targetObj = null;
                return;
            }

            // ���b�N�I���Ώۂ̌����A����Ȃ烍�b�N�I���A���Ȃ��Ȃ�J�����p�x�����Z�b�g
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

        // ���b�N�I���J�[�\��
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
            // �{�^���������ꂽ���̏���
            lockonInput = true;
            //Debug.Log("lockonInput: " + lockonInput);
            break;

        case InputActionPhase.Canceled:
            // �{�^���������ꂽ���̏���
            break;
        }
    }

    /// <summary>
    /// ���b�N�I���Ώۂ̌v�Z�������s���擾����
    /// �v�Z��3�̍H���ɕ������
    /// </summary>
    /// <returns></returns>
    GameObject GetLockonTarget()
    {
        // 1. SphereCastAll���g����Player���ӂ�Enemy���擾��List�Ɋi�[
        RaycastHit[] hits = Physics.SphereCastAll(originTrn.position, lockonRange, Vector3.up, 0, lockonLayers);

        if (hits ? .Length == 0)
        {
            // �͈͓��Ƀ^�[�Q�b�g�Ȃ�
            return null;
        }

        // 2. 1�̃��X�g�S�Ă�ray���΂��ː����ʂ���̂�����List��
        List<GameObject> hitObjects = makeListRaycastHit(hits);
        if (hitObjects ? .Count == 0)
        {
            // �ː����ʂ����^�[�Q�b�g�Ȃ�
            return null;
        }

        // 3. 2�̃��X�g�S�Ẵx�N�g���ƃJ�����̃x�N�g�����r���A��ʒ����Ɉ�ԋ߂����̂�T��
        var tumpleData = GetOptimalEnemy(hitObjects);

        float degreemum = tumpleData.Item1;
        GameObject target = tumpleData.Item2;

        //// ���߂���ԏ������l�����l��菬�����ꍇ�A�^�[�Q�b�e�B���O���I���ɂ��܂�
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

    // 2. 1�̃��X�g�S�Ă�ray���΂��ː����ʂ���̂�����List��
    // Raycast�̔��ˈʒu�ɂ���Ă͎����f���ɓ������ĎՕ������������ꍇ������
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

    // 3. 2�̃��X�g�S�Ẵx�N�g���ƃJ�����̃x�N�g�����r���A��ʒ����Ɉ�ԋ߂����̂�T��
    // degreep: �J�����̑O���x�N�g��X,Z��������Ȃ�p�x
    private (float, GameObject) GetOptimalEnemy(List<GameObject> hitObjects)
    {
        float degreep = Mathf.Atan2(cameraTrn.forward.x, cameraTrn.forward.z);
        float degreemum = Mathf.PI * 2;
        GameObject target = null;

        foreach(var enemy in hitObjects)
        {
            // pos: �G����J�����֌������x�N�g��
            // pos2: �J��������G�Ɍ������x�N�g��(���������ɐ������Đ��K��)
            Vector3 pos = cameraTrn.position - enemy.transform.position;
            Vector3 pos2 = enemy.transform.position - cameraTrn.position;
            pos2.y = 0.0f;
            pos2.Normalize();

            // degree: pos2��X,Z��������Ȃ�p�x. �J�����̑O������ǂꂾ����]���Ă��邩
            float degree = Mathf.Atan2(pos2.x, pos2.z);
            // degree��-180���`180���ɐ��K��
            degree = degreeNormalize(degree, degreep);

            // pos.magnitude: �G�ƃJ�����̋���
            // pos.magnitude�ɉ����Ċp�x�ɏd�݂������A�������߂��قǊp�x�̏d�݂��傫���I�D�����
            degree = degree + degree * (pos.magnitude / 500) * lockonFactor;
            // Mathf.Abs(degreemum): �ȑO�ɋL�^���ꂽ�ŏ��p�x���̐�Βl
            // Mathf.Abs(degree): ���݂̊p�x���̐�Βl
            if (Mathf.Abs(degreemum) >= Mathf.Abs(degree))
            {
                degreemum = degree;
                target = enemy;
            }
        }
        return (degreemum, target);
    }

    // degree��-180���`180���ɐ��K��
    private float degreeNormalize(float degree, float degreep)
    {
        if (Mathf.PI <= (degreep - degree))
        {
            // degreep (�J�����̑O���x�N�g��) ��degree (�J��������G�ւ̃x�N�g��) �Ƃ̊p�x����180���ȏ�
            // degree����360�������Đ��K��(-180����180�ɐ���)
            degree = degreep - degree - Mathf.PI * 2;
        }
        else if (-Mathf.PI >= (degreep - degree))
        {
            // degreep (�J�����̑O���x�N�g��) ��degree (�J��������G�ւ̃x�N�g��) �Ƃ̊p�x����-180���ȉ�
            // degree����360�������Đ��K��(-180����180�ɐ���)
            degree = degreep - degree + Mathf.PI * 2;
        }
        else
        {
            // ���̂܂�degree���g�p
            degree = degreep - degree;
        }
        return degree;
    }

    // �}�E�X�A�E�X�e�B�b�N���͎��̏���
    private GameObject GetLockonTargetLeftOrRight(string direction)
    {
        float degreemum;
        GameObject target;
        //GameObject current = null;
        // 1. SphereCastAll���g����Player���ӂ�Enemy���擾��List�Ɋi�[
        RaycastHit[] hits = Physics.SphereCastAll(originTrn.position, lockonRange, Vector3.up, 0, lockonLayers);
        // 2. 1�̃��X�g�S�Ă�ray���΂��ː����ʂ���̂�����List��
        List<GameObject> hitObjects = makeListRaycastHit(hits);
        // 3. 2�̃��X�g�S�Ẵx�N�g���ƃJ�����̃x�N�g�����r���A��ʒ����Ɉ�ԋ߂����̂�T��
        if (direction.Equals("left"))
        {
            // �����͎�
            var tumpleData = GetEnemyLeftOrRight(hitObjects, "left");
            degreemum = tumpleData.Item1;
            target = tumpleData.Item2;
        }
        else
        {
            // �E���͎�
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
            // pos: �G����J�����֌������x�N�g��
            // pos2: �J��������G�Ɍ������x�N�g��(���������ɐ������Đ��K��)
            Vector3 pos = cameraTrn.position - enemy.transform.position;
            Vector3 pos2 = enemy.transform.position - cameraTrn.position;
            pos2.y = 0.0f;
            pos2.Normalize();

            // degree: pos2��X,Z��������Ȃ�p�x. �J�����̑O������ǂꂾ����]���Ă��邩
            float degree = Mathf.Atan2(pos2.x, pos2.z);
            // degree��-180���`180���ɐ��K��
            degree = degreeNormalize(degree, degreep);
            if (direction.Equals("left"))
            {
                if (degree < 0)
                {
                    // enemy����ʒ������E���ɂ���ꍇ��₩��O��
                    continue;
                }
            }
            else
            {
                if (degree > 0)
                {
                    // enemy����ʒ�����荶���ɂ���ꍇ��₩��O��
                    continue;
                }
            }
            // pos.magnitude: �G�ƃJ�����̋���
            // pos.magnitude�ɉ����Ċp�x�ɏd�݂������A�������߂��قǊp�x�̏d�݂��傫���I�D�����
            degree = degree + degree * (pos.magnitude / 500) * lockonFactor;
            // Mathf.Abs(degreemum): �ȑO�ɋL�^���ꂽ�ŏ��p�x���̐�Βl
            // Mathf.Abs(degree): ���݂̊p�x���̐�Βl
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