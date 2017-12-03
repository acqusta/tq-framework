
#ifndef _TDBAPI_H_
#define _TDBAPI_H_

#include "TDBAPIStruct.h"

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(_WINDOWS)
#define __PLATFORM_WINDOWS__
#else
#define __PLATFORM_LINUX__
#endif

#ifdef __PLATFORM_WINDOWS__
    #ifdef TDB_API_EXPORT
        #define TDBAPI __declspec(dllexport)
    #else    
        #define TDBAPI __declspec(dllimport)
    #endif
#else
    #define TDBAPI
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/************************************************************************/
	//����ֵ˵��������ο�TDB_ERROR
	//TDB_SUCCESS: �ɹ�
	//TDB_INVALID_PARAMS: ��Ч�Ĳ���(hTdb��Ч��pReqΪ�գ�pCountΪ��)
	//TDB_NETWORK_ERROR���������Ӵ���
	//TDB_NO_DATA: û������
	//TDB_NETWORK_TIMEOUT:��ʱ
	//TDB_OUT_OF_MEMORY���ڴ�ľ�
/************************************************************************/

/**
	���ܣ���һ����TDB�����������ӣ�������ӳɹ����򷵻����Ӿ����ʧ�ܷ���NULL��
	* @param[in]   OPEN_SETTINGS*			pSetting;	OPEN_SETTINGS�ṹ������
	* @param[out]  TDBDefine_ResLogin*		loginRes;	��¼���
	* @return THANDLE���
*/
TDBAPI THANDLE TDB_Open(const OPEN_SETTINGS* pSetting, TDBDefine_ResLogin* loginRes);

/**
	���ܣ������һ����TDB�����������ӣ�������ӳɹ����򷵻����Ӿ����ʧ�ܷ���NULL��
	* @param[in]   OPEN_SETTINGS*			pSetting;		OPEN_SETTINGS����
	* @param[in]  TDB_PROXY_SETTING*		pProxySetting;	TDB_PROXY_SETTING��������
	* @param[out]  TDBDefine_ResLogin*		loginRes;		��¼���
	* @return THANDLE���
*/
TDBAPI THANDLE TDB_OpenProxy(const OPEN_SETTINGS* pSetting, TDB_PROXY_SETTING* pProxySetting, TDBDefine_ResLogin* loginRes);

/**
	���ܣ������ر����ӣ�������Handle
	* @param[in]  THANDLE hTdb;		��¼���صľ��
	* @return �رս��
*/
TDBAPI int TDB_Close(THANDLE hTdb);

/**
	���ܣ���ȡ�������õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE			hTdb;		��¼���صľ��
	* @param[in]  char*				szMarket;	�г�(��ʽ:Market-Level-Source(SZ-2-0)),Ϊ������������Ȩ�г�
	* @param[out]  TDBDefine_Code**	pCodeTable; �����
	* @param[out]  int*				pCount;		���������
	* @return
*/
TDBAPI int TDB_GetCodeTable(THANDLE hTdb, const char* szMarket, TDBDefine_Code** pCodeTable, int* pCount);

/**
	���ܣ���ȡ�������ϸ��Ϣ,������Ӷϵ�����δ���ӣ��򷵻�NULL�����ص�ָ����API�û������ͷ�֮
	* @param[in]  THANDLE hTdb;			��¼���صľ��
	* @param[in]  char*	  szWindCode;	��ô���(000001.SZ)
	* @param[in] char*	  strMarket;	�г�(��ʽ:Market-Level-Source(SZ-2-0))
	* @return TDBDefine_Code* ������Ϣ
*/
TDBAPI const TDBDefine_Code* TDB_GetCodeInfo(THANDLE hTdb, const char* szWindCode, const char* strMarket);

/**
	���ܣ���ȡK�ߣ���õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE				hTdb;	��¼���صľ��
	* @param[in]  TDBDefine_ReqKLine*	pReq;	����ṹ��(����(TickBar)ʱ����Ϊ7����Ȼ�գ�������Ϊ30����Ȼ��)
	* @param[out] TDBDefine_KLine**		pData;	K�߽��
	* @param[out] int*					pCount;	K������
	* @return ����״̬
*/
TDBAPI int TDB_GetKLine(THANDLE hTdb, const TDBDefine_ReqKLine* pReq, TDBDefine_KLine** pData, int* pCount);

/**
	���ܣ���ȡTick���ݣ���õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE				hTdb;	��¼���صľ��
	* @param[in]  TDBDefine_ReqTick*	pReq;	����ṹ��
	* @param[out] TDBDefine_Tick**		pData;	Tick���
	* @param[out] int*					pCount;	Tick����
	* @return ����״̬
*/
TDBAPI int TDB_GetTick(THANDLE hTdb, const TDBDefine_ReqTick* pReq, TDBDefine_Tick** pData, int* pCount);

/**
	���ܣ���ȡ��ʳɽ����ݣ���õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE					hTdb;	��¼���صľ��
	* @param[in]  TDBDefine_ReqTransaction*	pReq;	����ṹ��
	* @param[out] TDBDefine_Transaction**	pData;	Transaction���
	* @param[out] int*						pCount;	Transaction����
	* @return ����״̬
*/
TDBAPI int TDB_GetTransaction(THANDLE hTdb, const TDBDefine_ReqTransaction* pReq, TDBDefine_Transaction** pData, int* pCount);

/**
	���ܣ���ȡ���ί�����ݣ���õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE					hTdb;	��¼���صľ��
	* @param[in]  TDBDefine_ReqOrder*		pReq;	����ṹ��
	* @param[out] TDBDefine_Order**			pData;	Order���
	* @param[out] int*						pCount;	Order����
	* @return ����״̬
*/
TDBAPI int TDB_GetOrder(THANDLE hTdb, const TDBDefine_ReqOrder* pReq, TDBDefine_Order** pData, int* pCount);

/**
	���ܣ���ȡί�ж������ݣ���õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE					hTdb;	��¼���صľ��
	* @param[in]  TDBDefine_ReqOrderQueue*	pReq;	����ṹ��
	* @param[out] TDBDefine_OrderQueue**    pData;	OrderQueue���
	* @param[out] int*						pCount;	OrderQueue����
	* @return ����״̬
*/
TDBAPI int TDB_GetOrderQueue(THANDLE hTdb, const TDBDefine_ReqOrderQueue* pReq, TDBDefine_OrderQueue** pData, int* pCount);

/**
	���ܣ�����ָ�깫ʽ
	* @param[in]  THANDLE					hTdb;		��¼���ؾ��
	* @param[in]  char*						szName;		��ʽ
	* @param[in]  char*						szContent;	��ʽ����
	* @param[out]  TDBDefine_AddFormulaRes*	pRes;		���ؽ��
	* @return ����״̬
*/
TDBAPI int TDB_AddFormula(THANDLE hTdb, const char* szName, const char* szContent, TDBDefine_AddFormulaRes* pRes);

/**
	���ܣ���ȡ�������ϵ�ָ�깫ʽ����õĽ����Ҫ�û��������� TDB_Free���ͷ�
	* @param[in]  THANDLE					hTdb;			��¼���صľ��
	* @param[in]  char*						szFormulaName;	��ʽ���ƣ�Ϊ""��������ڵ�ȫ����ʽ
	* @param[out] TDBDefine_FormulaItem**   pFormula;		ָ�깫ʽ���
	* @param[out] int*						pCount;			ָ�깫ʽ����
	* @return ����״̬
*/
TDBAPI int TDB_GetFormula(THANDLE hTdb, const char* szFormulaName, TDBDefine_FormulaItem** pFormula, int *pCount);

//��ȡ�����֮��Ӧ��������TDB_ReleaseCalcFormula�ͷ��ڴ�
/**
	���ܣ���ȡָ�깫ʽ��������Ӧ��������TDB_ReleaseCalcFormula�ͷ��ڴ�
	* @param[in]  THANDLE					hTdb;			��¼���صľ��
	* @param[in]  TDBDefine_ReqCalcFormula*	szFormulaName;	ָ�깫ʽ��������
	* @param[out] TDBDefine_CalcFormulaRes* pFormula;		ָ�깫ʽ������
	* @return ����״̬
*/
TDBAPI int TDB_CalcFormula(THANDLE hTdb, const TDBDefine_ReqCalcFormula* pReqCalc, TDBDefine_CalcFormulaRes* pResult);


/**
	���ܣ�ɾ��ָ�깫ʽ
	* @param[in]  THANDLE					hTdb;			��¼���ؾ��
	* @param[in]  char*						szFormulaName;  ��ʽ��
	* @param[out]  TDBDefine_DelFormulaRes*	pDelRes;		���ؽ��
	* @return ����״̬
*/
TDBAPI int TDB_DeleteFormula(THANDLE hTdb, const char* szFormulaName, TDBDefine_DelFormulaRes* pDelRes);

/**
	���ܣ��ͷ�TDB_CalcFormula���û�ȡ��TDBDefine_CalcFormulaResult����еĶ�̬�ڴ棬pResult���뱻 TDB_CalcFormula��ʼ����
	* @param[in]  TDBDefine_CalcFormulaRes*	pResult; ָ�깫ʽ���
	* @return void
*/
TDBAPI void TDB_ReleaseCalcFormula(TDBDefine_CalcFormulaRes* pResult);

/**
	���ܣ��ͻ������ͷ�
	* @param[in]  void*	p; ��Ҫ�ͷŵ�ָ��
	* @return void
*/
TDBAPI void TDB_Free(void* p);

#ifdef __cplusplus
}
#endif

#endif//_TDBAPI_H_
