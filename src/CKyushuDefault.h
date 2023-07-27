#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KyushuServer
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// ��������
	enum KyushuMsgType
	{
		RETURN_USER_FAIL_MSG		= 1002,		// ʧ����Ϣ
	
		USER_REQUEST_LOGIN_PARA,				// �����¼
		RETURN_USER_LOGIN_MSG,					// ��¼����

		USER_REQUEST_VIEW_ROLE_PARA,			// �����ɫ
		RETURN_USER_REQ_VIEW_ROLE_MSG,			// ������ɫ�б�

		USER_REQUEST_REG_ACCOUNT_PARA,			// ע���˻�
		RETURN_USER_REG_ACCOUNT_MSG,			// ע�ᷴ��

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �Ӱ�����
	enum KyushuSubMsgType
	{
		// ��¼��ʽ
		e_msg_account_login_mode	= 10001,	// �˻�����
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ��Ϣ�ȼ�
	enum enumMsgLevel
	{
		level_high		= 0,					// ��
		level_normal,							// ��
		level_low								// ��
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ѹ����־
	enum enumMsgFlag
	{
		msgflag_normal		= 0,				// ��ͨ��־
		msgflag_compress	= 0x01,				// ѹ����־
		msgflag_encrypt		= 0x01 << 1,		// ���ܱ�־
	};
#pragma pack(push, 1)

	////////////////////////////////////////////////////////////////////////////////////////////////
	enum EKyushuErrorCode
	{
		EKEC_BEGIN					= 10001,

		EKEC_RECV_SIZE_ABNORMAL,				// �������ߴ��쳣, �Ƿ����ݻ�ߴ�
		EKEC_RECV_STREAM_ABNORMAL,				// ��������ѹʧ��, ��ƥ���ѹ����ʽ�������ݳ�����ѹ�ߴ�����

		EKEC_LOGIN_ACCOUNT,						// �˻�
		EKEC_LOGIN_PASSWORD,					// ����
		EKEC_LOGIN_MODE,						// ��¼ģʽ�쳣
		EKEC_LOGIN_WAIT,						// �ظ����� (�Ѿ��ύ��¼��������ڴ�����)
		EKEC_LOGIN_STATE_ABNORMAL,				// ��ǰ״̬�쳣 (�����ϵ�¼״̬, ���쳣���ݰ����������쳣)
		EKEC_LOGIN_DB_FAIL,						// ����ʧ�� (DB)
		EKEC_LOGIN_FAIL,						// ��¼ʧ��
		EKEC_LOGIN_TIME_OUT,					// ��¼��ʱ (���Ӻ�һ��ʱ����δ���е�¼����)

		EKEC_LOGIN_NOT_STREAM,					// û�е�¼���д���Ƿ����ݰ�
		EKEC_AUTH_NOT,							// û��Ȩ��

		EKEC_VIEW_ROLE_LIST_NOT,				// �鿴�б��쳣 (�����쳣�����ݿ��ѯʧ��)

	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// �����ṹ
	struct MsgCommonHeader
	{
		uint32_t	stLength;					// ��Ϣ����
		char_t		cMsgFlag;					// ��Ϣ��־
	};

	struct MsgHeader : public MsgCommonHeader
	{
		MsgHeader()
		{
			dwType = 0;
			uMsgLevel = level_high;
			cMsgFlag = msgflag_normal;
		};

		int16_t		dwType;						// ��Ϣ����
		char_t		uMsgLevel;					// ��Ϣ�ȼ�
	};

	struct Msg : public MsgHeader
	{
		int32_t		GetType() { return dwType; }
		uint32_t	GetLength() { return stLength; }
		int32_t		GetLevel() { return static_cast<int32_t>(uMsgLevel); }
		void_t		SetLevel(enumMsgLevel lev) { uMsgLevel = static_cast<char_t>(lev); }
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// ʧ�ܴ���
	struct stReturnServerFailCmd : public Msg
	{
		stReturnServerFailCmd()
		{
			dwType = RETURN_USER_FAIL_MSG;
			stLength = sizeof(stReturnServerFailCmd);

			byType = 0;
			byReturn = 0;
			memset(text, 0, sizeof(text));
			return;
		}

		char_t		text[128];					// ����
		int32_t		byType;						// �������
		uint8_t		byReturn;					// 0 = ʧ��, 1 = �ɹ�
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �˻���¼
	struct stUserRequestLoginCmd : public Msg
	{
		stUserRequestLoginCmd()
		{
			dwType = USER_REQUEST_LOGIN_PARA;
			stLength = sizeof(stUserRequestLoginCmd);

			subtype = 0;
			memset(name, 0, sizeof(name));
			memset(password, 0, sizeof(password));
			return;
		};

		int16_t GetSubType() { return subtype; }

		int16_t			subtype;				// 10001 = ��ͨ��¼
		char_t			name[33];				// �˻�
		char_t			password[65];			// ����
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ��¼�ɹ�
	struct stServerReturnLoginSuccessCmd : public Msg
	{
		stServerReturnLoginSuccessCmd()
		{
			dwType = RETURN_USER_LOGIN_MSG;
			stLength = sizeof(stServerReturnLoginSuccessCmd);

			uid = 0;
			cgys = 0;
			memset(nickname, 0, sizeof(nickname));
			memset(rolename, 0, sizeof(rolename));
			return;
		};

		int64_t			uid;					// �˻�UID
		char_t			nickname[65];			// ����
		char_t			rolename[33];			// ��ɫ������
		int64_t			cgys;					// Ȩ�� �ɹ����� ������ 64λ����64��Ȩ��
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �鿴��ɫ
	struct stUserRequestViewRoleCmd : public Msg
	{
		stUserRequestViewRoleCmd()
		{
			dwType = USER_REQUEST_VIEW_ROLE_PARA;
			stLength = sizeof(stUserRequestViewRoleCmd);

			page = 0;
			number = 0;
			return;
		};

		int32_t page;
		int32_t number;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ɫ��Ϣ
	struct _view_role_info
	{
		_view_role_info()
		{
			uid = 0;
			xtgl = 0;
			cgys = 0;

			memset(name, 0, sizeof(name));
			return;
		};

		int64_t		uid;				// UID
		char_t		name[32];			// ��ɫ������
		int64_t		xtgl;				// Ȩ�� ϵͳ����
		int64_t		cgys;				// Ȩ�� �ɹ�����
	};

	struct stServerReturnViewRoleCmd : public Msg
	{
		stServerReturnViewRoleCmd()
		{
			dwType = RETURN_USER_REQ_VIEW_ROLE_MSG;
			stLength = sizeof(stServerReturnViewRoleCmd);

			subtype = 0;
			index = 0;
			dataarray = nullptr;
			return;
		};

		int16_t				subtype;	// ������
		uint32_t			index;		// λ��
		int32_t				count;		// �������� (���������Ϊʵ������, ��ֵ����Ϊ��)
		_view_role_info*	dataarray;	// ����ʵ��
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ɫ
	struct stUserRequestRegRoleCmd : public Msg
	{
		stUserRequestRegRoleCmd()
		{

		};


	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// �����˻�����
	struct stServerReturnReqAccountCmd : public Msg
	{
		stServerReturnReqAccountCmd()
		{
			dwType = RETURN_USER_REG_ACCOUNT_MSG;
			stLength = sizeof(stServerReturnReqAccountCmd);

			uid = 0;
			memset(username, 0, sizeof(username));
			memset(nickname, 0, sizeof(nickname));
			return;
		};

		int16_t			state;					// 0=ʧ�� 1=�ɹ�
		int64_t			uid;					// UID
		char_t			username[32];			// �˻�
		char_t			nickname[64];			// ����
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Ȩ�޼��
#define CheckAuthority(num, n)			GetValueBit(num, n)

	// ϵͳȨ��
	enum EnumSystemAuth
	{
		AUTH_SYS_SETTINGS,			// ϵͳ����
		AUTH_SYS_ROLE,				// ��ɫ����
		AUTH_SYS_ACCOUNT,			// ����Ա����
	};
#define CheckUserSysAuth(n)				GetValueBit(m_user_info.r_xtgl, n)


#pragma pack(pop)
};