#ifndef __TDF_API_STRUCT_H__ 
#define __TDF_API_STRUCT_H__
#pragma  pack(push)
#pragma pack(1)

#ifndef THANDLE
typedef void* THANDLE;
#endif

#ifndef __int64
#define __int64 long long
#endif
#define MAXSERVER 4

/******************************************************************* ��Ϣͷ *********************************************************************/
struct TDF_APP_HEAD
{
	int	nHeadSize;         //����¼�ṹ��С
	int	nItemCount;	       //��¼����
	int	nItemSize;         //��¼��С
};
struct TDF_MSG
{
	unsigned short  	    sFlags;		        //16λ ��ʶ��.
	int  	                nDataType;	        //16λ �������� ��enum TDF_MSG_ID
	int			            nDataLen;	        //32λ ���ݳ��ȣ�������TDF_APP_HEAD�ĳ��ȣ�
	int			            nServerTime;		//32λ������ʱ�������ȷ������HHMMSSmmm��������ԭ��ѹ�������Ǳ���ʱ��
	int     		        nOrder;		        //32λ ��ˮ��
	int                     nConnectId;         //����ID����TDF_Open�ǣ����������趨��ֵ
	TDF_APP_HEAD*           pAppHead;	        //Ӧ��ͷ
	void*                   pData;              //����ָ��
};
/*******************************************************************  �ص����� *********************************************************************/
//���ݻص�������֪ͨ�û��յ������顢��ʳɽ������ί�У�ί�ж��е�,pMsgHead->pAppHead->ItemCount�ֶο��Ի�֪�õ��˶�������¼��pMsgHead->pAppHead->pDataָ���һ�����ݼ�¼
typedef void (*TDF_DataMsgHandler)  (THANDLE hTdf, TDF_MSG* pMsgHead);    
//ϵͳ��Ϣ�ص�������֪ͨ�û��յ�������Ͽ��¼������ӣ��������������������ȡ�����ȡϵͳ��Ϣʱ��pMsgHead->pAppHeadָ��Ϊ��, pMsgHead->pDataָ����Ӧ�Ľṹ��
typedef void (*TDF_SystemMsgHandler)(THANDLE hTdf, TDF_MSG* pMsgHead);  

/******************************************************************* ��Ϣ���Ͷ��� *********************************************************************/
//��Ϣ���Ͷ�Ӧ�Ľṹ�������
enum TDF_MSG_ID
{
    MSG_INVALID = -100,
    //ϵͳ��Ϣ
    MSG_SYS_DISCONNECT_NETWORK,     //����Ͽ��¼�, ��Ӧ�Ľṹ��ΪNULL
    MSG_SYS_CONNECT_RESULT,         //�����������ӵĽ��
    MSG_SYS_LOGIN_RESULT,           //��½Ӧ��
    MSG_SYS_CODETABLE_RESULT,       //��ȡ�������
    MSG_SYS_QUOTATIONDATE_CHANGE,   //�������ڱ��֪ͨ
    MSG_SYS_MARKET_CLOSE,           //����
    MSG_SYS_HEART_BEAT,             //������������Ϣ, ��Ӧ�Ľṹ��ΪNULL
    //������Ϣ
    MSG_DATA_INDEX,                 //ָ������
    MSG_DATA_MARKET,                //��������
    MSG_DATA_FUTURE,                //�ڻ�����
    MSG_DATA_TRANSACTION,           //��ʳɽ�
    MSG_DATA_ORDERQUEUE,            //ί�ж���
    MSG_DATA_ORDER,                 //���ί��
	MSG_DATA_BBQTRANSACTION,        //BBQ��ȯ�ɽ�����
	MSG_DATA_BBQBID,                //BBQ��ȯ��������

	MSG_SYS_PACK_OVER   = -10,              //��ǰ������������
};

/******************************************************************* ϵͳ��Ϣ *********************************************************************/
//MSG_SYS_PACK_OVER
struct TDF_PACK_OVER
{
	int nDataNumber;
	int nConID;
};
//��������MSG_SYS_CONNECT_RESULT
struct TDF_CONNECT_RESULT
{
    char szIp[32];
    char szPort[8];
    char szUser[64];
    char szPwd[64];

    unsigned int nConnResult; //Ϊ0���ʾ����ʧ�ܣ���0���ʾ���ӳɹ�
    int nConnectionID;        //����ID
};
//��������MSG_SYS_LOGIN_RESULT
struct TDF_LOGIN_RESULT
{
    unsigned int nLoginResult;//Ϊ0���ʾ��½��֤ʧ�ܣ���0���ʾ��֤�ɹ�

    char szInfo[256];       //��½����ı�
    int nMarkets;           //�г�����
    char szMarket[256][8];  //�г����� SZ, SH, CF, SHF, CZC, DCE
    int nDynDate[256];      //��̬��������
};
//��������MSG_SYS_CODETABLE_RESULT
struct TDF_CODE_RESULT
{
    char szInfo[128];       //��������ı�
    int nMarkets;           //�г�����
    char szMarket[256][8];  //�г�����
    int nCodeCount[256];    //���������
    int nCodeDate[256];     //���������

};
//��������MSG_SYS_QUOTATIONDATE_CHANGE
struct TDF_QUOTATIONDATE_CHANGE
{
    char szMarket[8];	    //�г�����
    int nOldDate;	        //ԭ��������
    int nNewDate;	        //����������
};
//��������MSG_SYS_MARKET_CLOSE
struct TDF_MARKET_CLOSE
{
    char    szMarket[8];        //����������
    int		nTime;				//ʱ��(HHMMSSmmm)
    char	chInfo[64];			//������Ϣ
};

/******************************************************************* ����� *********************************************************************/
//ʹ��TDF_GetCodeTable��ȡ���������ʹ��TDF_GetOptionCodeInfo��ȡ��Ȩ�������Ȩ��������Ϣ��
struct TDF_CODE
{
    char szWindCode[32];    //Wind Code: AG1302.SHF
    char szMarket[8];       //market code: SHF
    char szCode[32];        //original code:ag1302
    char szENName[32];
    char szCNName[32];      //chinese name: ����1302
    int nType;                            
};
struct TDF_OPTION_CODE
{
    TDF_CODE basicCode;
    
    char szContractID[32];// ��Ȩ��Լ����
    char szUnderlyingSecurityID[32];//// ���֤ȯ����
    char chCallOrPut;               // �Ϲ��Ϲ�C1        �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
    int  nExerciseDate;             // ��Ȩ��Ȩ�գ�YYYYMMDD    
    //�����ֶ�
    char chUnderlyingType;			// ���֤ȯ����C3    0-A�� 1-ETF (EBS �C ETF�� ASH �C A ��)
	char chOptionType;              // ŷʽ��ʽC1        ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
	
	char chPriceLimitType;          // �ǵ�����������C1 ��N����ʾ���ǵ�����������, ��R����ʾ���ǵ�����������
	int  nContractMultiplierUnit;	// ��Լ��λ,         ������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
	int  nExercisePrice;            // ��Ȩ��Ȩ��,       ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
	int  nStartDate;                // ��Ȩ�׸�������,YYYYMMDD
	int  nEndDate;                  // ��Ȩ�������/��Ȩ�գ�YYYYMMDD
	int  nExpireDate;               // ��Ȩ�����գ�YYYYMMDD
};
union TD_EXCODE_INFO
{
	struct TD_OptionCodeInfo            //futures options ר�� (nType >= 0x90 && nType <= 0x95),����Ȩ�����ֶ���Ч
	{
		char chContractID[32];           // ��Ȩ��Լ����C19
		char szUnderlyingSecurityID[32]; // ���֤ȯ����
		char chUnderlyingType;			 // ���֤ȯ����C3    0-A�� 1-ETF (EBS �C ETF�� ASH �C A ��)
		char chOptionType;               // ŷʽ��ʽC1        ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
		char chCallOrPut;                // �Ϲ��Ϲ�C1        �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
		char chPriceLimitType;           // �ǵ�����������C1 ��N����ʾ���ǵ�����������, ��R����ʾ���ǵ�����������
		int  nContractMultiplierUnit;	 // ��Լ��λ,         ������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
		int  nExercisePrice;             // ��Ȩ��Ȩ��,       ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
		int  nStartDate;                 // ��Ȩ�׸�������,YYYYMMDD
		int  nEndDate;                   // ��Ȩ�������/��Ȩ�գ�YYYYMMDD
		int  nExerciseDate;              // ��Ȩ��Ȩ�գ�YYYYMMDD
		int  nExpireDate;                // ��Ȩ�����գ�YYYYMMDD
	}Option;
};
struct TDF_CODE_INFO
{
	int  nMarketID;           //������ID,��������
	int  nDataLevel;          //����Level
	int  nFlag;               //������Դ
	int  nType;					//֤ȯ����
	char chCode[32];            //֤ȯ����
	char chName[64];			//����֤ȯ����
	TD_EXCODE_INFO exCodeInfo;
};

//������ID����///////////////////////////////
#ifndef ID_MARKET_DEFINE
#define ID_MARKET_DEFINE
#define ID_MARKET_SZ	0	//����
#define ID_MARKET_SH	1	//�Ϻ�
#define ID_MARKET_PT	2	//PT
#define ID_MARKET_HZ	3	//���ָ��
#define ID_MARKET_SL	4	//�Զ����г�
#define ID_MARKET_MI	5	//�Զ���ָ��
#define ID_MARKET_HK	6	//�۹�
#define ID_MARKET_QH	7	//�ڻ�
#define ID_MARKET_FE	8	//���
#define ID_MARKET_KF	9	//���(�۹�)
#define ID_MARKET_CF	10	//�й�����ָ��

#define ID_MARKET_SHF	11	//�Ϻ�������Ʒ������
#define ID_MARKET_CZC	12	//֣����Ʒ
#define ID_MARKET_DCE	13	//������Ʒ
/////////////////////////////////////////////
#define ID_MARKET_CME	14  //֥�Ӹ���ҵ������
#define ID_MARKET_CBT	15  //֥�Ӹ��ڻ�������
#define ID_MARKET_CMX	16  //ŦԼ��Ʒ�ڻ�������
#define ID_MARKET_NYM	17  //ŦԼ��Ʒ������
#define ID_MARKET_NYB	18  //ŦԼ�ڻ�������
#define ID_MARKET_IPE	19	//�׶ع���ʯ�ͽ�����
#define ID_MARKET_LME	20	//�׶ؽ���������
#define ID_MARKET_N		21  //ŦԼ������
#define ID_MARKET_O		22  //��˹��˽�����
#define ID_MARKET_HKF	23  //��۽������ڻ�/��Ȩ
/////////////////////////////////////////////
#endif
/******************************************************************* ������Ϣ *********************************************************************/
//��������MSG_DATA_BBQTRANSACTION,     
struct TDF_BBQTRANSACTION_DATA
{
	char        szWindCode[32];         //600001.SH 
	int         nActionDay;             //ҵ������(��Ȼ��)
	int			nTime;					//ʱ��(HHMMSSmmm)
	int         nDoneID;                //�ɽ����۱��
	int			nPrice;				    //�ɽ�������(%)��۸� *10000
	char        chPriceStatus;          //�����ʻ�۸��ʶ	1�������� 	2���۸�
	char        chStatus;               //�����ʻ�۸��ʶ	1�������� 	2���۸�
	char        chDirection;            //�ɽ�����	1��done	2��gvn		3��tkn		4������
	char        chSource;               //���ۻ���	1������ 2��ƽ����˳ 3���г� 4���������	5������
	char        chSpecialFlag;          //��ʶ�����Ƿ�����Ȩ����	0�ޱ��	1��ע�а�������		2��ע�а�����Ȩ
};
//������MSG_DATA_BBQBID,    
struct TDF_BBQBID_DATA
{
	char        szWindCode[32];         //600001.SH 
	int         nActionDay;             //ҵ������(��Ȼ��)
	int			nTime;					//ʱ��(HHMMSSmmm)
	char        chSource;               //���ۻ���

	int         nBidPrice;		       //���������ʻ�۸� x10000
	__int64         nBidVolume;		   //������ x10000
	char        chBidPriceStatus;      //�����ʻ�۸��ʶ	1�������� 	2���۸�
	char        chIsBid;               //�Ƿ�bid	0������bid����ͨ���ۣ�	1����bid�����򱨼ۣ�
	char        chBidSpecialFlag;      //��ʶ�����Ƿ�����Ȩ����	0�ޱ��	1��ע�а�������		2��ע�а�����Ȩ
	char        chBidStatus;           //�������ű���״̬	0����������	1����������

	int         nOfrPrice;		       //���������ʻ�۸� x10000
	__int64         nOfrVolume;		   //������	�������ļ��ܣ���2000+1000���ͺϲ�Ϊ3000�����ַ����к�- - ����Ϊ0. x10000
	char        chOfrPriceStatus;      //�����ʻ�۸��ʶ	1�������� 	2���۸�
	char        chIsOfr;               //�Ƿ�ofr	0������ofr����ͨ���ۣ�	  1����ofr�����򱨼ۣ�
	char        chOfrSpecialFlag;      //��ʶ�����Ƿ�����Ȩ����	0�ޱ��	1��ע�а�������		2��ע�а�����Ȩ
	char        chOfrStatus;           //�������ű���״̬	0����������	1����������
};
//��������MSG_DATA_MARKET
struct TDF_MARKET_DATA
{
    char        szWindCode[32];         //600001.SH 
    char        szCode[32];             //ԭʼCode
    int         nActionDay;             //ҵ������(��Ȼ��)
    int         nTradingDay;            //������
    int			 nTime;					//ʱ��(HHMMSSmmm)
    int			 nStatus;				//״̬
    unsigned int nPreClose;				//ǰ���̼�
    unsigned int nOpen;					//���̼�
    unsigned int nHigh;					//��߼�
    unsigned int nLow;					//��ͼ�
    unsigned int nMatch;				//���¼�
    unsigned int nAskPrice[10];			//������
    unsigned int nAskVol[10];			//������
    unsigned int nBidPrice[10];			//�����
    unsigned int nBidVol[10];			//������
    unsigned int nNumTrades;			//�ɽ�����
    __int64		 iVolume;				//�ɽ�����
    __int64		 iTurnover;				//�ɽ��ܽ��
    __int64		 nTotalBidVol;			//ί����������
    __int64		 nTotalAskVol;			//ί����������
    unsigned int nWeightedAvgBidPrice;	//��Ȩƽ��ί��۸�
    unsigned int nWeightedAvgAskPrice;  //��Ȩƽ��ί���۸�
    int			 nIOPV;					//IOPV��ֵ��ֵ
    int			 nYieldToMaturity;		//����������
    unsigned int nHighLimited;			//��ͣ��
    unsigned int nLowLimited;			//��ͣ��
    char		 chPrefix[4];			//֤ȯ��Ϣǰ׺
    int			 nSyl1;					//��ӯ��1
    int			 nSyl2;					//��ӯ��2
    int			 nSD2;					//����2���Ա���һ�ʣ�
	const TDF_CODE_INFO *  pCodeInfo;     //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
//��������MSG_DATA_INDEX
struct TDF_INDEX_DATA
{
    char        szWindCode[32];         //600001.SH 
    char        szCode[32];             //ԭʼCode
    int         nActionDay;             //ҵ������(��Ȼ��)
    int         nTradingDay;            //������
    int         nTime;			        //ʱ��(HHMMSSmmm)
    int		    nOpenIndex;		        //����ָ��
    int 	    nHighIndex;		        //���ָ��
    int 	    nLowIndex;		        //���ָ��
    int 	    nLastIndex;		        //����ָ��
    __int64	    iTotalVolume;	        //���������Ӧָ���Ľ�������
    __int64	    iTurnover;		        //���������Ӧָ���ĳɽ����
    int		    nPreCloseIndex;	        //ǰ��ָ��
	const TDF_CODE_INFO *  pCodeInfo;   //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
//��������MSG_DATA_FUTURE
struct TDF_FUTURE_DATA
{
    char        szWindCode[32];         //600001.SH 
    char        szCode[32];             //ԭʼCode
    int         nActionDay;             //ҵ������(��Ȼ��)
    int         nTradingDay;            //������
    int			 nTime;					//ʱ��(HHMMSSmmm)	
    int			 nStatus;				//״̬
    __int64		 iPreOpenInterest;		//��ֲ�
    unsigned int nPreClose;				//�����̼�
    unsigned int nPreSettlePrice;		//�����
    unsigned int nOpen;					//���̼�	
    unsigned int nHigh;					//��߼�
    unsigned int nLow;					//��ͼ�
    unsigned int nMatch;				//���¼�
    __int64		 iVolume;				//�ɽ�����
    __int64		 iTurnover;				//�ɽ��ܽ��
    __int64		 iOpenInterest;			//�ֲ�����
    unsigned int nClose;				//������
    unsigned int nSettlePrice;			//�����
    unsigned int nHighLimited;			//��ͣ��
    unsigned int nLowLimited;			//��ͣ��
    int			 nPreDelta;			    //����ʵ��
    int			 nCurrDelta;            //����ʵ��
    unsigned int nAskPrice[5];			//������
    unsigned int nAskVol[5];			//������
    unsigned int nBidPrice[5];			//�����
    unsigned int nBidVol[5];			//������
	//Add 20140605
	int	nAuctionPrice;		            //�������жϲο���
	int	nAuctionQty;		            //�������жϼ��Ͼ�������ƥ����	
	int nAvgPrice;                      //֣�����ڻ�����
	const TDF_CODE_INFO *  pCodeInfo;   //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
//��������MSG_DATA_TRANSACTION
struct TDF_TRANSACTION
{
    char    szWindCode[32];             //600001.SH 
    char    szCode[32];                 //ԭʼCode
    int     nActionDay;                 //��Ȼ��
    int 	nTime;		                //�ɽ�ʱ��(HHMMSSmmm)
    int 	nIndex;		                //�ɽ����
    int		nPrice;		                //�ɽ��۸�
    int 	nVolume;	                //�ɽ�����
    int		nTurnover;	                //�ɽ����
    int     nBSFlag;                    //��������(��'B', ����'S', ������' ')
    char    chOrderKind;                //�ɽ����
    char    chFunctionCode;             //�ɽ�����
    int	    nAskOrder;	                //������ί�����
    int	    nBidOrder;	                //����ί�����
	const TDF_CODE_INFO *  pCodeInfo;   //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
//��������MSG_DATA_ORDER
struct TDF_ORDER
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //ԭʼCode
	int 	nActionDay;	    //ί������(YYMMDD)
	int 	nTime;			//ί��ʱ��(HHMMSSmmm)
	int 	nOrder;	        //ί�к�
	int		nPrice;			//ί�м۸�
	int 	nVolume;		//ί������
	char    chOrderKind;	//ί�����
	char    chFunctionCode;	//ί�д���('B','S','C')
	const TDF_CODE_INFO *  pCodeInfo;     //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
//��������MSG_DATA_ORDERQUEUE
struct TDF_ORDER_QUEUE
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //ԭʼCode
	int     nActionDay;     //��Ȼ��
	int 	nTime;			//ʱ��(HHMMSSmmm)
	int     nSide;			//��������('B':Bid 'A':Ask)
	int		nPrice;			//ί�м۸�
	int 	nOrders;		//��������
	int 	nABItems;		//��ϸ����
	int 	nABVolume[200];	//������ϸ
	const TDF_CODE_INFO *  pCodeInfo;     //������Ϣ�� TDF_Close�����������󣬴�ָ����Ч
};
/******************************************************************* ������� *********************************************************************/
enum DATA_TYPE_FLAG
{
	DATA_TYPE_TRANSACTION = 0x2,           //��ʳɽ�
	DATA_TYPE_ORDER       = 0x4,           //���ί��
	DATA_TYPE_ORDERQUEUE  = 0x8,           //ί�ж��� 
	DATA_TYPE_NONE = 0,                    //ֻҪ���飬�����������ģ����Ķ������DATA_TYPE_TRANSACTION | DATA_TYPE_ORDER | DATA_TYPE_ORDERQUEUE
};
enum SUBSCRIPTION_STYLE
{
	SUBSCRIPTION_FULL = 3,                //ȫ�г�����
	SUBSCRIPTION_SET=0,                   //����Ϊ�����б��й�Ʊ��
	SUBSCRIPTION_ADD=1,                   //���Ӷ����б��й�Ʊ
	SUBSCRIPTION_DEL=2,                   //ɾ���б��еĶ���
};

/******************************************************************* ���� *********************************************************************/
//�������ã��ڵ���TDF_Open֮ǰ����k
enum TDF_ENVIRON_SETTING
{
	TDF_ENVIRON_HEART_BEAT_INTERVAL,       //Heart Beat�����������, ��ֵΪ0���ʾĬ��ֵ10����
	TDF_ENVIRON_MISSED_BEART_COUNT,        //���û���յ����������������ֵ����û�յ������κ����ݣ����ж�Ϊ���ߣ���ֵ0ΪĬ�ϴ���2��
	TDF_ENVIRON_OPEN_TIME_OUT,             //�ڵ�TDF_Open�ڼ䣬����ÿһ�����ݰ��ĳ�ʱʱ�䣨����������TDF_Open�����ܵ����ȴ�ʱ�䣩����ֵΪ0��Ĭ��30��
	TDF_ENVIRON_USE_PACK_OVER,
};
//�����������ã����ö������ʵ�֣������������������Լ��ݾ�APIʹ�÷�����
//��Ⱦ�API�����ˣ�nReconnectCount��nReconnectGap��nProtocol��nDate
struct TDF_OPEN_SETTING
{
    char szIp[32];
    char szPort[8];
    char szUser[64];
    char szPwd[64];
	//�ص���������
	TDF_DataMsgHandler pfnMsgHandler;       //������Ϣ����ص�
	TDF_SystemMsgHandler pfnSysMsgNotify;   //ϵͳ��Ϣ֪ͨ�ص�

	//unsigned int nProtocol;                 //Э��ţ�Ϊ0��ΪĬ�ϣ�����0x6001
	//��������
	const char* szMarkets;                  // �г����ģ�����"SZ;SH;CF;SHF;DCE;SHF"����Ҫ���ĵ��г��б��ԡ�;���ָ�,Ϊ����������֧�ֵ��г�
	const char* szSubScriptions;            // ���붩�ģ�����"600000.sh;ag.shf;000001.sz"����Ҫ���ĵĹ�Ʊ���ԡ�;���ָΪ������ȫ�г�
	unsigned int nTypeFlags;                // �������Ͷ��ģ�֧�ֶ���3������TRANSACTION;ORDER;ORDERQUEUE�� ��ע�⣺���������κ�ʱ�򶼷��ͣ�����Ҫ����! �μ�enum DATA_TYPE_FLAG

	unsigned int nTime;                     //Ϊ0������ʵʱ���飬Ϊ0xffffffff��ͷ����
	unsigned int nConnectionID;             //����ID�����ӻص���Ϣ�ĸ��ӽṹ TDF_CONNECT_RESULT�� ��������ID
};

//�����������
struct TDF_SERVER_INFO
{
	char szIp[32];
	char szPort[8];
	char szUser[64]; //TODO
	char szPwd[64];
};
struct TDF_OPEN_SETTING_EXT
{
	//����������
	TDF_SERVER_INFO	siServer[MAXSERVER];
	unsigned int nServerNum; 
	//�ص���������
	TDF_DataMsgHandler pfnMsgHandler;       //������Ϣ����ص�
	TDF_SystemMsgHandler pfnSysMsgNotify;   //ϵͳ��Ϣ֪ͨ�ص�
	
	//unsigned int nProtocol;                 //Э��ţ�Ϊ0��ΪĬ�ϣ�����0x6001
	//��������
	const char* szMarkets;                  // �г����ģ�����"SZ;SH;CF;SHF;DCE;SHF"����Ҫ���ĵ��г��б��ԡ�;���ָ�,Ϊ����������֧�ֵ��г�
	const char* szSubScriptions;            // ���붩�ģ�����"600000.sh;ag.shf;000001.sz"����Ҫ���ĵĹ�Ʊ���ԡ�;���ָΪ������ȫ�г�
	unsigned int nTypeFlags;                // �������Ͷ��ģ�֧�ֶ���3������TRANSACTION;ORDER;ORDERQUEUE�� ��ע�⣺���������κ�ʱ�򶼷��ͣ�����Ҫ����! �μ�enum DATA_TYPE_FLAG

	unsigned int nTime;                     //Ϊ0������ʵʱ���飬Ϊ0xffffffff��ͷ����
	unsigned int nConnectionID;             //����ID�����ӻص���Ϣ�ĸ��ӽṹ TDF_CONNECT_RESULT�� ��������ID
};
//�������������
enum TDF_PROXY_TYPE
{
	TDF_PROXY_SOCK4,
	TDF_PROXY_SOCK4A,
	TDF_PROXY_SOCK5,
	TDF_PROXY_HTTP11,
};
struct TDF_PROXY_SETTING
{
	TDF_PROXY_TYPE nProxyType;
	char szProxyHostIp[32];
	char szProxyPort[8];
	char szProxyUser[32];
	char szProxyPwd[32];
};

#pragma pack(pop)
#endif
