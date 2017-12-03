#ifndef __TDF_API_H__
#define __TDF_API_H__

#include "TDFAPIStruct.h"
#include "TDFAPIVersion.h"

#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS)
#ifdef TDF_API_EXPORT
#define TDFAPI __declspec(dllexport) 
#else	
#define TDFAPI __declspec(dllimport)
#endif
#else
#define TDFAPI __attribute((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum TDF_ERR
{
    TDF_ERR_UNKOWN=-200,                // δ֪����

    TDF_ERR_INITIALIZE_FAILURE = -100,  // ��ʼ��socket����ʧ��
    TDF_ERR_NETWORK_ERROR,              // �������ӳ�������
    TDF_ERR_INVALID_PARAMS,             // ���������Ч
    TDF_ERR_VERIFY_FAILURE,             // ��½��֤ʧ�ܣ�ԭ��Ϊ�û�������������󣻳�����½����
    TDF_ERR_NO_AUTHORIZED_MARKET,       // ����������г���û����Ȩ
    TDF_ERR_NO_CODE_TABLE,              // ����������г����춼û�д����
    
    TDF_ERR_SUCCESS = 0,                // �ɹ�
};


//����TDF��������ֵ,�ڵ���TDF_Open֮ǰ����
//����ֵ��TDF_ERR_INVALID_PARAMS��ʾ��Ч��nEnv��TDF_ERR_SUCCESS��ʾ�ɹ�
TDFAPI int TDF_SetEnv(TDF_ENVIRON_SETTING nEnv, unsigned int nValue);


//ͬ���������򿪵�TDFServer�����ӣ�����ɹ����򷵻ؾ�������򷵻�NULL����TDF_Open�ڼ䷢��������Ͽ����������Զ�����
//�ڵ����ڼ䣬ϵͳ֪ͨ�������յ�MSG_SYS_CONNECT_RESULT��MSG_SYS_LOGIN_RESULT��MSG_SYS_CODETABLE_RESULT��Ϣ
//�������Ͽ�������յ�MSG_SYS_DISCONNECT_NETWORK��pErr�д�Ŵ�����룬ֻ���ڴ������Ϊ TDF_ERR_NETWORK_ERROR ʱ���ⲿ��Ӧ���������߼�
TDFAPI THANDLE TDF_Open(TDF_OPEN_SETTING* pSettings, TDF_ERR* pErr);
//�������ö����������ȡ�����������������������
TDFAPI THANDLE TDF_OpenExt(TDF_OPEN_SETTING_EXT* pSettings,TDF_ERR* pErr);
//ͨ����������ӣ��ص���Ϣ�ʹ�������TDF_Openһ��
TDFAPI THANDLE TDF_OpenProxy(TDF_OPEN_SETTING* pOpenSettings, TDF_PROXY_SETTING* pProxySettings, TDF_ERR* pErr);
TDFAPI THANDLE TDF_OpenProxyExt(TDF_OPEN_SETTING_EXT* pOpenSettings, TDF_PROXY_SETTING* pProxySettings, TDF_ERR* pErr);

//��ȡָ���г��Ĵ�������Ѿ��յ�MSG_SYS_CODETABLE_RESULT ��Ϣ֮�󣬿��Ի�ô����
//��ȡ���Ĵ������Ҫ����TDF_FreeArr���ͷ��ڴ�
TDFAPI int TDF_GetCodeTable(THANDLE hTdf, const char* szMarket, TDF_CODE** pCode, unsigned int* pItems);

// ����ô�������ȡ��ϸ����Ȩ������Ϣ
// pCodeInfoָ�����û��ṩ��
// ����ɹ���ȡ���򷵻�TDF_ERR_SUCCESS�����򷵻� TDF_ERR_NO_CODE_TABLE �� TDF_ERR_INVALID_PARAMS

TDFAPI int TDF_GetOptionCodeInfo(THANDLE hTdf, const char* szWindCode, TDF_OPTION_CODE* pCodeInfo);

//ͬ���������ر����ӣ���Ҫ�ٻص�����������ã�����Ῠ��
TDFAPI int TDF_Close(THANDLE hTdf);

TDFAPI void TDF_FreeArr(void *pArr);

//��½����; �˺����Ǹ��첽�����������TDF_Open�ɹ�֮�����
TDFAPI int TDF_SetSubscription(THANDLE hTdf, const char* szSubScriptions, SUBSCRIPTION_STYLE nSubStyle);

#ifdef __cplusplus
}
#endif

#endif