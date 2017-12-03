
#ifndef _TDBAPISTRUCT_H_
#define _TDBAPISTRUCT_H_

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(_WINDOWS)
#define __PLATFORM_WINDOWS__
#else
#define __PLATFORM_LINUX__
#endif


#ifdef __PLATFORM_LINUX__
#define __int64 long long
#endif


#pragma  pack(push)
#pragma pack(1)
///���������붨��////////////////////////////////////////////////////
//TDB���

#ifndef THANDLE
typedef void* THANDLE;
#endif

enum TDB_ERROR
{
    TDB_SUCCESS = 0,

    TDB_NETWORK_ERROR=-1,       //�������
    TDB_NETWORK_TIMEOUT=-2,     //���糬ʱ
    TDB_NO_DATA = -3,           //û������
    TDB_OUT_OF_MEMORY=-4,       //�ڴ�ľ�
    TDB_LOGIN_FAILED = -5,      //��½ʧ��
    TDB_INVALID_PARAMS=-11,     //��Ч�Ĳ���
    TDB_INVALID_CODE_TYPE,      //��Ч�Ĵ������ͣ�������TDB_GetFuture������ڻ����ʹ��룬����֮��
    
    
    TDB_WRONG_FORMULA=-50,      //ָ�깫ʽ����        
};



enum TDB_PROXY_TYPE
{
	TDB_PROXY_SOCK4,
	TDB_PROXY_SOCK4A,
	TDB_PROXY_SOCK5,
	TDB_PROXY_HTTP11,
};

struct TDB_PROXY_SETTING
{
	TDB_PROXY_TYPE nProxyType;
	char szProxyHostIp[64];
	char szProxyPort[8];
	char szProxyUser[32];
	char szProxyPwd[32];
};

struct OPEN_SETTINGS
{
    char szIP[24];              //������ip��ַ
    char szPort[8];             //�������˿�
    char szUser[32];            //�û���
    char szPassword[32];        //����

    unsigned int nTimeOutVal;   //��ȡ����ʱ��ָ�����糬ʱ��������Ϊ0����Ϊ2���ӣ���������nTimeOutVal���δ�յ���Ӧ���ݰ������ڲ���ر�����
    unsigned int nRetryCount;   //��ȡ����ʱ�������ߣ�ָ������������Ϊ0����������������nRetryCount��֮���Ե��ߣ��򷵻��������
    unsigned int nRetryGap;     //����֮��������ʱ������������Ϊ0����Ϊ1�룩
};

//��Ȩ��ʽ
typedef enum REFILLFLAG
{
    REFILL_NONE = 0,        //����Ȩ
    REFILL_BACKWARD=1,      //ȫ����ǰ��Ȩ�����������ȥ��
    REFILL_FORWARD=2,       //ȫ�����Ȩ���ӹ�ȥ�����ڣ�
} ;

typedef enum CYCTYPE
{
    CYC_SECOND,
    CYC_MINUTE,
    CYC_DAY,
    CYC_WEEK,
    CYC_MONTH,
    CYC_SEASON,
    CYC_HAFLYEAR,
    CYC_YEAR,
    CYC_TICKBAR,
};

//��������
typedef enum ORDERSIDE
{
    ORDERSIDE_BID = 0,      //��
    ORDERSIDE_ASK,          //��
} ;


///ϵͳ��Ϣ�ṹ��////////////////////////////////////////////////////

//��¼�ر�
struct TDBDefine_ResLogin
{
    char szInfo[64];             //��Ϣ
    int  nMarkets;               //֧���г�����
    char szMarket[256][24];       //�г���־(SZ, SH, CF, SHF, DCE, CZC,...)
    int  nDynDate[256];          //��̬��������
};

///������Ϣ�ṹ��////////////////////////////////////////////////////
struct TDBDefine_Code
{
    char chWindCode[32];        //��ô���(ag1312.SHF)
    char chCode[32];            //����������(ag1312)
    char chMarket[24];           //�г�����(SHF-1-0)
    char chCNName[32];          //֤ȯ��������
    char chENName[32];          //֤ȯӢ������
    int  nType;                 //֤ȯ����
};

///������Ϣ�ṹ��////////////////////////////////////////////////////
//K������ KLine
struct TDBDefine_ReqKLine
{
    char chCode[32];            //֤ȯ��ô���(ag1312.SHF)
	char chMarketKey[24];		//�г�����,�磺SH-1-0;SZ-2-0
    REFILLFLAG nCQFlag;         //��Ȩ��־������Ȩ����ǰ��Ȩ�����Ȩ
    int nCQDate;                //��Ȩ����(=0:ȫ�̸�Ȩ) ��ʽ��YYMMDD������20130101��ʾ2013��1��1��
    int nQJFlag;                //ȫ�۱�־(ծȯ)(0:���� 1:ȫ��)
    CYCTYPE nCycType;           //�������ڣ����ߡ����ӡ����ߡ����ߡ����ߡ����ߡ������ߡ����ߡ�TickBar
    int nCycDef;                //��������������nCycTypeȡֵ���롢���ӡ����ߡ����ߡ�����ʱ������ֶ���Ч��
    int nAutoComplete;          //�Զ����룺��1�����ߡ�1������֧�������־����1�����룻0�������룩
    int nBeginDate;             //��ʼ����(������,0:�ӽ��쿪ʼ)
    int nEndDate;               //��������(������,=0:��nBeginDateһ��) 
    int nBeginTime;             //��ʼʱ�䣬=0��ʾ�ӿ�ʼ����ʽ����HHMMSSmmm������94500000 ��ʾ 9��45��00��000����
    int nEndTime;               //����ʱ�䣬=0��ʾ����������ʽ����HHMMSSmmm������94500000 ��ʾ 9��45��00��000����
};

struct TDBDefine_KLine
{
    char chWindCode[32];            //��ô���(ag1312.SHF)
    char chCode[32];                //����������(ag1312)
    int nDate;                      //���ڣ���Ȼ�գ���ʽ��YYMMDD������20130101��ʾ2013��1��1�գ�0��ʾ����
    int nTime;                      //ʱ�䣨HHMMSSmmm������94500000 ��ʾ 9��45��00��000����
    int    nOpen;                   //����((a double number + 0.00005) *10000)
    int    nHigh;                   //���((a double number + 0.00005) *10000)
    int    nLow;                    //���((a double number + 0.00005) *10000)
    int    nClose;                  //����((a double number + 0.00005) *10000)
    __int64 iVolume;                //�ɽ���
    __int64    iTurover;            //�ɽ���(Ԫ)
    int    nMatchItems;             //�ɽ�����
    int nInterest;                  //�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
};

struct TDBDefine_Tick
{
    char chWindCode[32];                //��ô���(ag1312.SHF)
    char chCode[32];                    //����������(ag1312)
    int nDate;                          //���ڣ���Ȼ�գ�
    int nTime;                          //ʱ�䣨HHMMSSmmm������94500000 ��ʾ 9��45��00��000����
    int nPrice;                         //�ɽ���((a double number + 0.00005) *10000)
    __int64 iVolume;                    //�ɽ���
    __int64    iTurover;                //�ɽ���(Ԫ)
    int nMatchItems;                    //�ɽ�����
    int nInterest;                      //IOPV(����)����Ϣ(ծȯ)
    char chTradeFlag;                   //�ɽ���־
    char chBSFlag;                      //BS��־
    __int64 iAccVolume;                 //�����ۼƳɽ���
    __int64    iAccTurover;             //���ճɽ���(Ԫ)
    int nHigh;                          //���((a double number + 0.00005) *10000)
    int nLow;                           //���((a double number + 0.00005) *10000)
    int    nOpen;                       //����((a double number + 0.00005) *10000)
    int    nPreClose;                   //ǰ����((a double number + 0.00005) *10000)
	
	//�ڻ��ֶ�
	int nSettle;                        //�����((a double number + 0.00005) *10000)
	int nPosition;                       //�ֲ���
	int nCurDelta;                      //��ʵ��
	int nPreSettle;                    //�����((a double number + 0.00005) *10000)
	int nPrePosition;                  //��ֲ�

	//�������ֶ�
	int    nAskPrice[10];               //������((a double number + 0.00005) *10000)
	unsigned nAskVolume[10];            //������
	int    nBidPrice[10];               //�����((a double number + 0.00005) *10000)
	unsigned nBidVolume[10];            //������
	int    nAskAvPrice;                 //��Ȩƽ��������(�Ϻ�L2)((a double number + 0.00005) *10000)
	int    nBidAvPrice;                 //��Ȩƽ�������(�Ϻ�L2)((a double number + 0.00005) *10000)
	__int64  iTotalAskVolume;           //��������(�Ϻ�L2)
	__int64  iTotalBidVolume;           //��������(�Ϻ�L2)
   
	//������ֶ�ָ��ʹ��
    int        nIndex;                  //����Ȩָ��
    int        nStocks;                 //Ʒ������
    int        nUps;                    //����Ʒ����
    int        nDowns;                  //�µ�Ʒ����
    int        nHoldLines;              //��ƽƷ����

	//�����ֶ�
	int nResv1;//�����ֶ�1
	int nResv2;//�����ֶ�2
	int nResv3;//�����ֶ�3
};

struct TDBDefine_ReqTick
{
    char chCode[32];			//֤ȯ��ô���(ag1312.SHF)
	char chMarketKey[24];		//�г�����,�磺SH-1-0;SZ-2-0
    int  nDate;					//�������ڣ������գ�,Ϊ0��ӽ��죬��ʽ��YYMMDD������20130101��ʾ2013��1��1��
    int  nBeginTime;			//��ʼʱ�䣺��0���ͷ����ʽ����HHMMSSmmm������94500000 ��ʾ 9��45��00��000����
    int  nEndTime;				//����ʱ�䣺��0�������

	int nAutoComplete;			//�Զ������־:( 0�����Զ����룬1:�Զ����룩,�ݲ�֧��
};


//��ʳɽ����� Transaction
struct TDBDefine_ReqTransaction
{
    char chCode[32];            //֤ȯ��ô���(ag1312.SHF)
	char chMarketKey[24];		//�г�����,�磺SH-1-0;SZ-2-0
    int  nDate;					//��ʼ���ڣ������գ�����ʽYYMMDD
    int  nBeginTime;            //��ʼʱ��:0��ʾ��0��ʼ����ʽ��HHMMSSmmm
    int  nEndTime;              //����ʱ�䣺0��ʾ�����
};

struct TDBDefine_Transaction
{
    char    chWindCode[32];     //��ô���(ag1312.SHF)
    char    chCode[32];         //����������(ag1312)
    int     nDate;              //���ڣ���Ȼ�գ���ʽ:YYMMDD
    int     nTime;              //�ɽ�ʱ��(��ȷ������HHMMSSmmm)
    int     nIndex;             //�ɽ����
    char    chFunctionCode;     //�ɽ�����: 'C', 0
    char    chOrderKind;        //ί�����
    char    chBSFlag;           //BS��־
    int     nTradePrice;        //�ɽ��۸�((a double number + 0.00005) *10000)
    int     nTradeVolume;       //�ɽ�����
    int     nAskOrder;          //�������
    int     nBidOrder;          //�������
};

//���ί������ Order (SZ Level2 Only) 
typedef struct TDBDefine_ReqTransaction TDBDefine_ReqOrder ;

struct TDBDefine_Order
{
    char chWindCode[32];        //��ô���(ag1312.SHF)
    char chCode[32];            //����������(ag1312)
    int  nDate;                 //���ڣ���Ȼ�գ���ʽYYMMDD
    int  nTime;                 //ί��ʱ�䣨��ȷ������HHMMSSmmm��
    int  nIndex;                //ί�б��
    int  nOrder;                //������ί�к�
    char chOrderKind;           //ί�����
    char chFunctionCode;        //ί�д���, B, S, C
    int  nOrderPrice;           //ί�м۸�((a double number + 0.00005) *10000)
    int  nOrderVolume;          //ί������
};

//ί�ж������� OrderQueue
typedef struct TDBDefine_ReqTransaction TDBDefine_ReqOrderQueue;

struct TDBDefine_OrderQueue
{
    char    chWindCode[32];         //��ô���(ag1312.SHF)
    char    chCode[32];             //����������(ag1312)
    int     nDate;                  //���ڣ���Ȼ�գ���ʽYYMMDD
    int     nTime;                  //����ʱ��(��ȷ������HHMMSSmmm)
    int     nSide;                  //��������('B':Bid 'A':Ask)
    int     nPrice;                 //�ɽ��۸�((a double number + 0.00005) *10000)
    int     nOrderItems;            //��������
    int     nABItems;               //��ϸ����
    int     nABVolume[50];          //������ϸ
};

struct TDBDefine_AddFormulaRes
{
    int nErrLine;           //������
    char chText[132];       //������ָ�깫ʽ����
    char chInfo[68];        //������Ϣ
};

struct TDBDefine_FormulaItem
{
    char chFormulaName[28];    //ָ�깫ʽ����
    char chParam[132];         //����
};

struct TDBDefine_DelFormulaRes
{
    char chFormularName[28];    //ɾ����ָ������
    char chInfo[68];            //ɾ����Ϣ
};

struct TDBDefine_CalcFormulaRes
{
    char chWindCode[32];        //��ô���(ag1312.SHF)
    char chCode[32];            //����������(ag1312)

    int nRecordCount;           //��¼����
    int nFieldCount;            //�ֶ����������50��

    char chFieldName[50][28];   //�ֶ����ƣ�
    int* dataFileds[50];        //���50���ֶΣ���������ں�ʱ���ֶΣ���������ǰ��
};


//�������ָ�깫ʽ
struct TDBDefine_ReqCalcFormula
{
    char chFormulaName[28]; //��ʽ����
    char chParam[32];       //����, "N1=5,N2=10, N3='000001'
    char chCode[32];        //��ô��룬���磺AG1312.SHF
	char chMarketKey[24];		//�г�����,�磺SH-1-0;SZ-2-0

    CYCTYPE  nCycType;      //��������
    int  nCycDef;           //�������ڶ���

    REFILLFLAG  nCQFlag;    //��Ȩ��־
    int nBondDataType;      //ծȯȫ�۱�־

    int  nCQDate;           //��Ȩ����
    int  nCalcMaxItems;     //��������������
    int  nResultMaxItems;   //���͵Ľ�����������
};

#pragma pack(pop)

#endif//_TDBAPISTRUCT_H_
