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

		USER_REQUSET_SET_ROLE_PARA,				// 设置角色 (添加、更新、删除)

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

		// 角色
		e_msg_role_add,
		e_msg_role_update,
		e_msg_role_delete,
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

		EKEC_UID_FAIL,							// UID 异常
		EKEC_NAME_LEN_FAIL,						// 名称尺寸不正确

		EKEC_VIEW_ROLE_LIST_NOT,				// 查看列表异常 (网络异常或数据库查询失败)
		EKEC_SET_ROLE_INFO_FAIL,				// 设置角色信息数据异常 (非法的提交类型)

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

		wchar_t		text[128];					// 内容
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
		wchar_t			name[32];				// 账户
		wchar_t			password[64];			// 密码
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
		wchar_t			nickname[64];			// 名称
		wchar_t			rolename[32];			// 角色分组名
		int64_t			xtgl;					// 权限 系统管理
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
		wchar_t		name[32];			// 角色分组名
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
	// 设置角色 (添加、更新、删除)
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
		wchar_t			username[32];			// 账户
		wchar_t			nickname[64];			// 姓名
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 权限检查
	// 每种权限共计64位控制器 (占用8字节), 每一位代表一个不同的权限。0=关闭 1=正常
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
};