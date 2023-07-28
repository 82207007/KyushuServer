<<<<<<< Updated upstream
#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KyushuServer
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 主包类型
	enum KyushuMsgType
	{
		RETURN_USER_FAIL_MSG		= 1002,		// 失败消息
	
		USER_REQUEST_LOGIN_PARA,				// 请求登录
		RETURN_USER_LOGIN_MSG,					// 登录反馈

		USER_REQUEST_VIEW_ROLE_PARA,			// 浏览角色
		RETURN_USER_REQ_VIEW_ROLE_MSG,			// 反馈角色列表

		USER_REQUEST_REG_ACCOUNT_PARA,			// 注册账户
		RETURN_USER_REG_ACCOUNT_MSG,			// 注册反馈

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 子包类型
	enum KyushuSubMsgType
	{
		// 登录方式
		e_msg_account_login_mode	= 10001,	// 账户密码
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 消息等级
	enum enumMsgLevel
	{
		level_high		= 0,					// 高
		level_normal,							// 中
		level_low								// 低
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 压缩标志
	enum enumMsgFlag
	{
		msgflag_normal		= 0,				// 普通标志
		msgflag_compress	= 0x01,				// 压缩标志
		msgflag_encrypt		= 0x01 << 1,		// 加密标志
	};
#pragma pack(push, 1)

	////////////////////////////////////////////////////////////////////////////////////////////////
	enum EKyushuErrorCode
	{
		EKEC_BEGIN					= 10001,

		EKEC_RECV_SIZE_ABNORMAL,				// 数据流尺寸异常, 非法数据或尺寸
		EKEC_RECV_STREAM_ABNORMAL,				// 数据流解压失败, 非匹配的压缩方式或发送数据超出解压尺寸上限

		EKEC_LOGIN_ACCOUNT,						// 账户
		EKEC_LOGIN_PASSWORD,					// 密码
		EKEC_LOGIN_MODE,						// 登录模式异常
		EKEC_LOGIN_WAIT,						// 重复请求 (已经提交登录请求或正在处理中)
		EKEC_LOGIN_STATE_ABNORMAL,				// 当前状态异常 (不符合登录状态, 有异常数据包导致连接异常)
		EKEC_LOGIN_DB_FAIL,						// 请求失败 (DB)
		EKEC_LOGIN_FAIL,						// 登录失败
		EKEC_LOGIN_TIME_OUT,					// 登录超时 (连接后一定时间内未进行登录操作)

		EKEC_LOGIN_NOT_STREAM,					// 没有登录进行传输非法数据包
		EKEC_AUTH_NOT,							// 没有权限

		EKEC_VIEW_ROLE_LIST_NOT,				// 查看列表异常 (网络异常或数据库查询失败)

	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 基础结构
	struct MsgCommonHeader
	{
		uint32_t	stLength;					// 信息长度
		char_t		cMsgFlag;					// 信息标志
	};

	struct MsgHeader : public MsgCommonHeader
	{
		MsgHeader()
		{
			dwType = 0;
			uMsgLevel = level_high;
			cMsgFlag = msgflag_normal;
		};

		int16_t		dwType;						// 消息类型
		char_t		uMsgLevel;					// 消息等级
	};

	struct Msg : public MsgHeader
	{
		int32_t		GetType() { return dwType; }
		uint32_t	GetLength() { return stLength; }
		int32_t		GetLevel() { return static_cast<int32_t>(uMsgLevel); }
		void_t		SetLevel(enumMsgLevel lev) { uMsgLevel = static_cast<char_t>(lev); }
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 失败错误
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

		char_t		text[128];					// 内容
		int32_t		byType;						// 错误代码
		uint8_t		byReturn;					// 0 = 失败, 1 = 成功
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 账户登录
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

		int16_t			subtype;				// 10001 = 普通登录
		char_t			name[33];				// 账户
		char_t			password[65];			// 密码
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 登录成功
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

		int64_t			uid;					// 账户UID
		char_t			nickname[65];			// 名称
		char_t			rolename[33];			// 角色分组名
		int64_t			cgys;					// 权限 采购允许 长整数 64位控制64个权限
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 查看角色
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
	// 反馈角色信息
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
		char_t		name[32];			// 角色分组名
		int64_t		xtgl;				// 权限 系统管理
		int64_t		cgys;				// 权限 采购运输
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

		int16_t				subtype;	// 子类型
		uint32_t			index;		// 位置
		int32_t				count;		// 数据数量 (如果可能则为实际数量, 此值可能为空)
		_view_role_info*	dataarray;	// 数据实体
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 创建角色
	struct stUserRequestRegRoleCmd : public Msg
	{
		stUserRequestRegRoleCmd()
		{

		};


	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 创建账户反馈
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

		int16_t			state;					// 0=失败 1=成功
		int64_t			uid;					// UID
		char_t			username[32];			// 账户
		char_t			nickname[64];			// 姓名
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 权限检查
#define CheckAuthority(num, n)			GetValueBit(num, n)

	// 系统权限
	enum EnumSystemAuth
	{
		AUTH_SYS_SETTINGS,			// 系统设置
		AUTH_SYS_ROLE,				// 角色设置
		AUTH_SYS_ACCOUNT,			// 操作员设置
	};
#define CheckUserSysAuth(n)				GetValueBit(m_user_info.r_xtgl, n)


#pragma pack(pop)
=======
锘�#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KyushuServer
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 涓诲寘绫诲瀷
	enum KyushuMsgType
	{
		RETURN_USER_FAIL_MSG		= 1002,		// 澶辫触娑堟伅
	
		USER_REQUEST_LOGIN_PARA,				// 璇锋眰鐧诲綍
		RETURN_USER_LOGIN_MSG,					// 鐧诲綍鍙嶉

		USER_REQUEST_VIEW_ROLE_PARA,			// 娴忚瑙掕壊
		RETURN_USER_REQ_VIEW_ROLE_MSG,			// 鍙嶉瑙掕壊鍒楄〃

		USER_REQUSET_SET_ROLE_PARA,				// 璁剧疆瑙掕壊 (娣诲姞銆佹洿鏂般�佸垹闄�)

		USER_REQUEST_REG_ACCOUNT_PARA,			// 娉ㄥ唽璐︽埛
		RETURN_USER_REG_ACCOUNT_MSG,			// 娉ㄥ唽鍙嶉

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 瀛愬寘绫诲瀷
	enum KyushuSubMsgType
	{
		// 鐧诲綍鏂瑰紡
		e_msg_account_login_mode	= 10001,	// 璐︽埛瀵嗙爜

		// 瑙掕壊
		e_msg_role_add,
		e_msg_role_update,
		e_msg_role_delete,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 娑堟伅绛夌骇
	enum enumMsgLevel
	{
		level_high		= 0,					// 楂�
		level_normal,							// 涓�
		level_low								// 浣�
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鍘嬬缉鏍囧織
	enum enumMsgFlag
	{
		msgflag_normal		= 0,				// 鏅�氭爣蹇�
		msgflag_compress	= 0x01,				// 鍘嬬缉鏍囧織
		msgflag_encrypt		= 0x01 << 1,		// 鍔犲瘑鏍囧織
	};
#pragma pack(push, 1)

	////////////////////////////////////////////////////////////////////////////////////////////////
	enum EKyushuErrorCode
	{
		EKEC_BEGIN					= 10001,

		EKEC_RECV_SIZE_ABNORMAL,				// 鏁版嵁娴佸昂瀵稿紓甯�, 闈炴硶鏁版嵁鎴栧昂瀵�
		EKEC_RECV_STREAM_ABNORMAL,				// 鏁版嵁娴佽В鍘嬪け璐�, 闈炲尮閰嶇殑鍘嬬缉鏂瑰紡鎴栧彂閫佹暟鎹秴鍑鸿В鍘嬪昂瀵镐笂闄�

		EKEC_LOGIN_ACCOUNT,						// 璐︽埛
		EKEC_LOGIN_PASSWORD,					// 瀵嗙爜
		EKEC_LOGIN_MODE,						// 鐧诲綍妯″紡寮傚父
		EKEC_LOGIN_WAIT,						// 閲嶅璇锋眰 (宸茬粡鎻愪氦鐧诲綍璇锋眰鎴栨鍦ㄥ鐞嗕腑)
		EKEC_LOGIN_STATE_ABNORMAL,				// 褰撳墠鐘舵�佸紓甯� (涓嶇鍚堢櫥褰曠姸鎬�, 鏈夊紓甯告暟鎹寘瀵艰嚧杩炴帴寮傚父)
		EKEC_LOGIN_DB_FAIL,						// 璇锋眰澶辫触 (DB)
		EKEC_LOGIN_FAIL,						// 鐧诲綍澶辫触
		EKEC_LOGIN_TIME_OUT,					// 鐧诲綍瓒呮椂 (杩炴帴鍚庝竴瀹氭椂闂村唴鏈繘琛岀櫥褰曟搷浣�)

		EKEC_LOGIN_NOT_STREAM,					// 娌℃湁鐧诲綍杩涜浼犺緭闈炴硶鏁版嵁鍖�
		EKEC_AUTH_NOT,							// 娌℃湁鏉冮檺

		EKEC_UID_FAIL,							// UID 寮傚父
		EKEC_NAME_LEN_FAIL,						// 鍚嶇О灏哄涓嶆纭�

		EKEC_VIEW_ROLE_LIST_NOT,				// 鏌ョ湅鍒楄〃寮傚父 (缃戠粶寮傚父鎴栨暟鎹簱鏌ヨ澶辫触)
		EKEC_SET_ROLE_INFO_FAIL,				// 璁剧疆瑙掕壊淇℃伅鏁版嵁寮傚父 (闈炴硶鐨勬彁浜ょ被鍨�)

	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鍩虹缁撴瀯
	struct MsgCommonHeader
	{
		uint32_t	stLength;					// 淇℃伅闀垮害
		char_t		cMsgFlag;					// 淇℃伅鏍囧織
	};

	struct MsgHeader : public MsgCommonHeader
	{
		MsgHeader()
		{
			dwType = 0;
			uMsgLevel = level_high;
			cMsgFlag = msgflag_normal;
		};

		int16_t		dwType;						// 娑堟伅绫诲瀷
		char_t		uMsgLevel;					// 娑堟伅绛夌骇
	};

	struct Msg : public MsgHeader
	{
		int32_t		GetType() { return dwType; }
		uint32_t	GetLength() { return stLength; }
		int32_t		GetLevel() { return static_cast<int32_t>(uMsgLevel); }
		void_t		SetLevel(enumMsgLevel lev) { uMsgLevel = static_cast<char_t>(lev); }
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 澶辫触閿欒
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

		wchar_t		text[128];					// 鍐呭
		int32_t		byType;						// 閿欒浠ｇ爜
		uint8_t		byReturn;					// 0 = 澶辫触, 1 = 鎴愬姛
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 璐︽埛鐧诲綍
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

		int16_t			subtype;				// 10001 = 鏅�氱櫥褰�
		wchar_t			name[32];				// 璐︽埛
		wchar_t			password[64];			// 瀵嗙爜
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鐧诲綍鎴愬姛
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

		int64_t			uid;					// 璐︽埛UID
		wchar_t			nickname[64];			// 鍚嶇О
		wchar_t			rolename[32];			// 瑙掕壊鍒嗙粍鍚�
		int64_t			xtgl;					// 鏉冮檺 绯荤粺绠＄悊
		int64_t			cgys;					// 鏉冮檺 閲囪喘鍏佽 闀挎暣鏁� 64浣嶆帶鍒�64涓潈闄�
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鏌ョ湅瑙掕壊
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
	// 鍙嶉瑙掕壊淇℃伅
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
		wchar_t		name[32];			// 瑙掕壊鍒嗙粍鍚�
		int64_t		xtgl;				// 鏉冮檺 绯荤粺绠＄悊
		int64_t		cgys;				// 鏉冮檺 閲囪喘杩愯緭
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

		int16_t				subtype;	// 瀛愮被鍨�
		uint32_t			index;		// 浣嶇疆
		int32_t				count;		// 鏁版嵁鏁伴噺 (濡傛灉鍙兘鍒欎负瀹為檯鏁伴噺, 姝ゅ�煎彲鑳戒负绌�)
		_view_role_info*	dataarray;	// 鏁版嵁瀹炰綋
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 璁剧疆瑙掕壊 (娣诲姞銆佹洿鏂般�佸垹闄�)
	struct stUserRequestSetRoleCmd : public Msg
	{
		stUserRequestSetRoleCmd()
		{
			dwType = USER_REQUSET_SET_ROLE_PARA;
			stLength = sizeof(stUserRequestSetRoleCmd);

			subtype = 0;
			sn = 0;
			xtgl = 0;
			cgys = 0;
			memset(name, 0, sizeof(name));
			return;
		};

		int16_t				subtype;	// e_msg_role_add, e_msg_role_update
		int64_t				sn;
		wchar_t				name[32];
		int64_t				xtgl;
		int64_t				cgys;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鍒涘缓璐︽埛鍙嶉
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

		int16_t			state;					// 0=澶辫触 1=鎴愬姛
		int64_t			uid;					// UID
		wchar_t			username[32];			// 璐︽埛
		wchar_t			nickname[64];			// 濮撳悕
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 鏉冮檺妫�鏌�
	// 姣忕鏉冮檺鍏辫64浣嶆帶鍒跺櫒 (鍗犵敤8瀛楄妭), 姣忎竴浣嶄唬琛ㄤ竴涓笉鍚岀殑鏉冮檺銆�0=鍏抽棴 1=姝ｅ父
#define CheckAuthority(num, n)			GetValueBit(num, n)

	// 绯荤粺鏉冮檺
	enum EnumSystemAuth
	{
		AUTH_SYS_SETTINGS,			// 绯荤粺璁剧疆
		AUTH_SYS_ROLE,				// 瑙掕壊璁剧疆
		AUTH_SYS_ACCOUNT,			// 鎿嶄綔鍛樿缃�
	};
#define CheckUserSysAuth(n)				GetValueBit(m_user_info.r_xtgl, n)


#pragma pack(pop)
>>>>>>> Stashed changes
};