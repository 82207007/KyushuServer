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
		USER_REQUEST_MANAGE_ROLE_PARA,			// 角色管理 (添加、更新、删除)
		RETURN_USER_MANAGE_ROLE_MSG,			// 角色管理反馈

		USER_REQUEST_VIEW_ACCOUNT_PARA,			// 浏览账户
		RETURN_USER_REQ_VIEW_ACCOUNT_MSG,		// 反馈账户列表
		USER_REQUEST_MANAGE_ACCOUNT_PARA,		// 账户管理 (添加、更新、删除)
		RETURN_USER_MANAGE_ACCOUNT_MSG,			// 账户管理反馈

		USER_REQUEST_CGYS_PARA,					// 采购运输
		RETURN_USER_CGYS_MSG,					// 采购运输 反馈

		USER_REQUEST_CGYS_DEBT_PARA,			// 采购运输 借款
		RETURN_USER_CGYS_DEBT_MSG,				// 采购运输 借款 反馈

		USER_REQUEST_CGYS_ROUTINE_PARA,			// 采购运输 报销
		RETURN_USER_CGYS_ROUTINE_MSG,			// 采购运输 报销 反馈

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 子包类型
	enum KyushuSubMsgType
	{
		// 登录方式
		e_msg_account_login_mode = 10001,	// 账户密码

		// 角色
		e_msg_role_add,
		e_msg_role_update,
		e_msg_role_delete,

		// 账户
		e_msg_account_add,
		e_msg_account_update,
		e_msg_account_update2,
		e_msg_account_delete,

		// 数据为空
		e_msg_data_null,			// 浏览查询时数据为空 (已经到尾记录)


		// 采购运输 子类型
		e_msg_cgys_status,					// 状态
		e_msg_cgys_create,					// 新的采购单
		e_msg_cgys_loading,					// 装货 
		e_msg_cgys_unloading,				// 卸货
		e_msg_cgys_chargeback,				// 退单
		e_msg_cgys_destroy,					// 销毁
		e_msg_cgys_view_all,				// 查询
		e_msg_cgys_view_uid,				// 查询 sn
		e_msg_cgys_view_tid,				// 查询 票号

		// 采购运输 借/还款 子类型
		e_msg_cgys_jk_status,				// 状态
		e_msg_cgys_jk_create,				// 申请
		e_msg_cgys_jk_ratify,				// 审批
		e_msg_cgys_jk_overy,				// 还款
		e_msg_cgys_jk_chargeback,			// 退单 (借款人)
		e_msg_cgys_jk_view_all,				// 模糊查询 全部
		e_msg_cgys_jk_view_name,			// 模糊查询 全部 (按名称)
		e_msg_cgys_jk_view_uid,				// 精确查询 UID

		// 采购运输 报销 子类型 (同上)
		e_msg_cgys_bx_status,
		e_msg_cgys_bx_create,
		e_msg_cgys_bx_ratify,
		e_msg_cgys_bx_chargeback,
		e_msg_cgys_bx_view_all,
		e_msg_cgys_bx_view_name,
		e_msg_cgys_bx_view_uid,
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

	KyushuEventBegin
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
		EKEC_STRING_LEN_FAIL,					// 字符串尺寸不正确

		EKEC_VIEW_ROLE_LIST_NOT,				// 查看列表异常 (网络异常或数据库查询失败)
		EKEC_SET_ROLE_INFO_FAIL,				// 设置角色信息数据异常 (非法的提交类型)

		EKEC_SET_ACCOUNT_INFO_FAIL,				// 同角色

		
		EKEC_DATA_INVALID,						// 提交的数据异常 (缺少必要数据或必要数据为空)
		EKEC_UID_SERVER_BUSY,					// UID 服务器繁忙, 重新请求即可。
		EKEC_DATA_SERVER_BUSY,					// 数据 服务器网络繁忙，重新请求即可。
		EKEC_TIME_INVALID,						// 未知的时间格式

		EKEC_INVALID_COMMID,					// 未知的指令
		EKEC_INVALID_CONTROLID,					// 未知的控制码
	};

	// 错误代码: 内码
	enum EKyushuErrorCode2
	{
		EKEC2_NULL,
		EKEC2_DB_EXEC,				// 数据繁忙

		EKEC2_ACCOUNT_EXISTS,		// 账户已存在
		EKEC2_ACCOUNT_NOT,			// 账户不存在
		EKEC2_ACCOUNT_STOP,			// 账户已停权
		EKEC2_ACCOUNT_ONLINE,		// 账户已登录
		EKEC2_ACCOUNT_NOT_ROLE,		// 账户未分配角色分组
		EKEC2_ACCOUNT_LOGOUT,		// 账户已退出

		EKEC2_ROLE_EXISTS,			// 角色已存在
		EKEC2_ROLE_NOT,				// 角色不存在

		EKEC2_PASSWORD_NOT,			// 密码不正确
		EKEC2_UPDATE_FAIL,			// 数据更新失败


		// 采购运输
		EKEC2_UID_TICKET_EXISTS,	// 已经存在相同单据
		EKEC2_UID_STATUS_INVALID,	// 当前单据不存在或者单据状态已不符合要求
		EKEC2_SUB_COMMID_INVALID,	// 未知的命令
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

	// 时间格式
	struct TIMESTAMP
	{	
		TIMESTAMP()
		{
			memset(this, 0, sizeof(TIMESTAMP));
			return;
		};

		void_t reset()
		{
			year = 1970;
			month = day = 1;

			hour = 8;
			minute = second = 0;

			fraction = 0;
			return;
		};

		int16_t    year;
		uint16_t   month;
		uint16_t   day;
		uint16_t   hour;
		uint16_t   minute;
		uint16_t   second;
		uint32_t   fraction;
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

		int16_t			subtype;				// e_msg_account_login_mode
		wchar_t			name[32];				// 账户	(>=8)
		wchar_t			password[64];			// 密码	(>=6)
	};

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

		int32_t page;							// 页码			(1)
		int32_t number;							// 每页显示数量	(10)
	};


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

		int16_t				subtype;	// 子类型	e_msg_data_null 为此值时记录为空或已到尾记录后(可配合count验证)
		uint32_t			index;		// 位置
		int32_t				count;		// 数据数量	(如果可能则为实际数量, 此值可能为空)
		_view_role_info*	dataarray;	// 数据实体
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设置角色 (添加、更新、删除)
	struct stUserRequestManageRoleCmd : public Msg
	{
		stUserRequestManageRoleCmd()
		{
			dwType = USER_REQUEST_MANAGE_ROLE_PARA;
			stLength = sizeof(stUserRequestManageRoleCmd);

			subtype = 0;
			sn = 0;
			xtgl = 0;
			cgys = 0;
			memset(name, 0, sizeof(name));
			return;
		};

		/*
		* 创建:
		*	sn=0; name=val; xtgl=val; cgys=val;
		* 更新:
		*	sn=val; 其他同上
		* 删除
		*	sn=val;	其他可以为空
		*/
		int16_t				subtype;	// e_msg_role_add, e_msg_role_update, e_msg_role_delete
		int64_t				sn;			// 创建时此值为0即可
		wchar_t				name[32];	// 角色分组名	(>3)
		int64_t				xtgl;		// 权限 系统管理
		int64_t				cgys;		// 权限 仓储运输
	};

	// 反馈角色管理
	struct stServerReturnManageRoleCmd : public Msg
	{
		stServerReturnManageRoleCmd()
		{
			dwType = RETURN_USER_MANAGE_ROLE_MSG;
			stLength = sizeof(stServerReturnManageRoleCmd);

			state = false;
			errcode = 0;
			memset(text, 0, sizeof(text));
			return;
		};

		bool_t				state;		// 状态 1=成功 0=失败
		int32_t				errcode;	// 错误代码
		wchar_t				text[128];	// 附加字符串
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 查看账户
	struct stUserRequestViewAccountCmd : public Msg
	{
		stUserRequestViewAccountCmd()
		{
			dwType = USER_REQUEST_VIEW_ACCOUNT_PARA;
			stLength = sizeof(stUserRequestViewAccountCmd);

			page = 0;
			number = 0;
			return;
		};

		int32_t page;							// 页码			(1)
		int32_t number;							// 每页显示数量	(10)
	};


	// 反馈账户信息
	struct _view_account_info
	{
		_view_account_info()
		{
			sn = 0; r_sn = 0;
			state = false; online = false;
			memset(name, 0, sizeof(name));
			memset(nickname, 0, sizeof(nickname));
			return;
			return;
		};

		int64_t		sn;				// UID
		wchar_t		name[32];		// 账户
		wchar_t		nickname[64];	// 名称
		int64_t		r_sn;			// 角色 UID
		int16_t		state;			// 状态		0=禁用, 1=启用
		int64_t		online;			// 是否在线	0=离线，否则为在线
	};

	struct stServerReturnViewAccountCmd : public Msg
	{
		stServerReturnViewAccountCmd()
		{
			dwType = RETURN_USER_REQ_VIEW_ACCOUNT_MSG;
			stLength = sizeof(stServerReturnViewAccountCmd);

			subtype = 0;
			index = 0;
			dataarray = nullptr;
			return;
		};

		int16_t				subtype;	// 子类型	e_msg_data_null 为此值时记录为空或已到尾记录后(可配合count验证)
		uint32_t			index;		// 位置
		int32_t				count;		// 数据数量	(如果可能则为实际数量, 此值可能为空)
		_view_account_info*	dataarray;	// 数据实体
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设置账户 (添加、更新、删除)
	struct stUserRequestManageAccountCmd : public Msg
	{
		stUserRequestManageAccountCmd()
		{
			dwType = USER_REQUEST_MANAGE_ACCOUNT_PARA;
			stLength = sizeof(stUserRequestManageAccountCmd);

			subtype = 0;
			sn = 0;
			r_sn = 0;
			state = 0;
			memset(name, 0, sizeof(name));
			memset(pwd, 0, sizeof(pwd));
			memset(nickname, 0, sizeof(nickname));
			return;
		};

		/*
		* 创建:
		*	sn=0; name=val; r_sn=val(可=0但不建议); pwd=val; nickname=val; state=val;
		* 更新1(同时强制更新密码):
		*	sn=val; 其他同上
		* 更新2(密码不会更新):
		*	sn=val; 其他同上; pwd=可以为空;
		* 删除
		*	sn=val;	其他可以为空
		*/
		int16_t				subtype;		// e_msg_account_add, e_msg_account_update, e_msg_account_update2, e_msg_account_delete
		int64_t				sn;				// 创建时此值为0即可
		wchar_t				name[32];		// 非创建时此值可以为空
		int64_t				r_sn;			// 角色 UID (绑定角色分组)
		wchar_t				pwd[64];		// 密码 (必要时需要) (>=6)
		wchar_t				nickname[64];	// 姓名 (>3)
		int16_t				state;			// 0=停用 1=启用
	};

	// 反馈账户管理
	struct stServerReturnManageAccountCmd : public Msg
	{
		stServerReturnManageAccountCmd()
		{
			dwType = RETURN_USER_MANAGE_ACCOUNT_MSG;
			stLength = sizeof(stServerReturnManageAccountCmd);

			state = false;
			errcode = 0;
			memset(text, 0, sizeof(text));
			return;
		};

		bool_t				state;		// 状态 1=成功 0=失败
		int32_t				errcode;	// 错误代码
		wchar_t				text[128];	// 附加字符串
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 采购运输
	struct _cgys_submit_document
	{
		_cgys_submit_document()
		{
			unitprice = 0.0f;
			sn = 0; a_sn = 0;

			memset(unit, 0, sizeof(unit));
			memset(notes, 0, sizeof(notes));
			memset(supplier, 0, sizeof(supplier));
			memset(classify, 0, sizeof(classify));
			memset(ticketnumber, 0, sizeof(ticketnumber));
			memset(supplierphone, 0, sizeof(supplierphone));

			return;
		};

		int64_t			sn;					// 保留 (采购 UID)
		int64_t			a_sn;				// 保留 (账户 UID)
		wchar_t			ticketnumber[32];	// 票号
		wchar_t			supplier[120];		// 供货商
		wchar_t			supplierphone[32];	// 供货商电话
		wchar_t			classify[10];		// 分类
		float_t			unitprice;			// 单价
		wchar_t			unit[10];			// 单位
		wchar_t			notes[200];			// 备注
	};

	struct _cgys_submit_loading
	{
		_cgys_submit_loading()
		{
			memset(this, 0, sizeof(_cgys_submit_loading));
			return;
		};
		
		// 参考 _cgys_return_data_view_info
		int64_t			sn;					// 采购 UID
		wchar_t			carnumber[20];		// 车牌号
		float_t			number;				// 数量
		wchar_t			location[120];		// 地点
		wchar_t			locate[32];			// GPS
		wchar_t			image1[80];			// 照片1
		wchar_t			image2[80];			// 照片2
		wchar_t			notes[200];			// 备注
	};

	struct _cgys_submit_unloading
	{
		_cgys_submit_unloading()
		{
			memset(this, 0, sizeof(_cgys_submit_unloading));
			return;
		};

		int64_t			sn;					// 采购 UID
		wchar_t			location[120];		// 地点
		wchar_t			locate[32];			// GPS
		wchar_t			image1[80];			// 照片1
		wchar_t			image2[80];			// 照片2
		float_t			totalprice;			// 总额
	};

	struct _cgys_submit_chargeback
	{
		_cgys_submit_chargeback()
		{
			memset(this, 0, sizeof(_cgys_submit_chargeback));
			return;
		};

		// 参考 _cgys_return_data_view_info
		int64_t			sn;					// 采购 UID
		wchar_t			carnumber[20];		// 车牌号
	};

	struct _cgys_submit_destroy
	{
		_cgys_submit_destroy()
		{
			memset(this, 0, sizeof(_cgys_submit_destroy));
			return;
		};

		int64_t			sn;					// 采购 UID
	};

	struct _cgys_submit_document_view_all
	{
		_cgys_submit_document_view_all()
		{
			mode = 0;
			pageindex = 0; pagenumber = 0;
			status = 0;

			timeend.reset();
			timebegin.reset();
			return;
		};

		int32_t			mode;			// 0=无,1=状态,2=时间,3=状态+时间
		int32_t			pageindex;		// 页码 (>0)
		int32_t			pagenumber;		// 数量 (>5 && <100)
		int32_t			status;			// 参考 _cgys_return_data_view_info
		TIMESTAMP		timebegin;		// 起始时间
		TIMESTAMP		timeend;		// 结束时间
	};


	struct _cgys_submit_document_view_uid
	{
		_cgys_submit_document_view_uid()
		{
			sn = 0;
			return;
		};

		int64_t			sn;
	};

	struct _cgys_submit_document_view_tid
	{
		_cgys_submit_document_view_tid()
		{
			memset(this, 0, sizeof(_cgys_submit_document_view_tid));
			return;
		};

		wchar_t			ticketnumber[32];	// 票号
	};

	// 请求结构
	struct stUserRequestCgysManagerCmd : public Msg
	{
		stUserRequestCgysManagerCmd()
		{
			dwType = USER_REQUEST_CGYS_PARA;
			stLength = sizeof(stUserRequestCgysManagerCmd);

			subtype = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置

		// 联合结构体
#ifdef _union_struct
#if e_msg_cgys_create
		_cgys_submit_document			data;
#elif e_msg_cgys_loading
		_cgys_submit_loading			data;
#elif e_msg_cgys_unloading
		_cgys_submit_unloading			data;
#elif e_msg_cgys_chargeback
		_cgys_submit_chargeback			data;
#elif e_msg_cgys_destroy
		_cgys_submit_destroy			data;
#elif e_msg_cgys_view_all
		_cgys_submit_document_view_all	data;
#elif e_msg_cgys_view_uid
		_cgys_submit_document_view_uid	data;
#elif e_msg_cgys_view_tid
		_cgys_submit_document_view_tid	data;
#endif
#endif		
	};

	// 采购运输 反馈
	struct _cgys_return_status_info
	{
		_cgys_return_status_info()
		{
			memset(this, 0, sizeof(_cgys_return_status_info));
		};

		bool_t				state;		// 状态 1=成功 0=失败
		int32_t				errcode;	// 错误代码
		wchar_t				text[128];	// 附加字符串
	};

	struct _cgys_return_data_view_info
	{
		_cgys_return_data_view_info()
		{
			memset(this, 0, sizeof(_cgys_return_data_view_info));
			return;
		};

		int64_t			sn;					// UID			采购单
		int64_t			a_sn;				// UID			账户
		int32_t			status;				// 状态			0=停用(退单),1=填单,2=装车,3=卸车
		wchar_t			ticketnumber[32];	// 票号			(>8)
		wchar_t			supplier[120];		// 供货商		
		wchar_t			supplierphone[32];	// 供货商电话
		wchar_t			classify[10];		// 分类
		float_t			unitprice;			// 单价
		wchar_t			unit[10];			// 单位
		wchar_t			notes1[200];		// 备注
		TIMESTAMP		createtime;			// 创建时间

		float_t			totalprice;			// 总价

		wchar_t			carnumber[20];		// 车牌号		(>3)
		float_t			number;				// 数量			(>0)

		struct tempdata
		{
			tempdata()
			{
				memset(this, 0, sizeof(tempdata));
				return;
			};

			wchar_t		location[120];		// 地点		(>3)
			wchar_t		locate[32];			// GPS		(>8)
			wchar_t		image1[80];			// 照片1		(>5)
			wchar_t		image2[80];			// 照片2		(>5)
		};
		tempdata		planinfo[2];		// 进度数据
		wchar_t			notes2[200];		// 备注
		TIMESTAMP		begintime;			// 接取时间
		TIMESTAMP		endtime;			// 完成时间
	};

	struct stServerReturnCgysManagerCmd : public Msg
	{
		stServerReturnCgysManagerCmd()
		{
			dwType = RETURN_USER_CGYS_MSG;
			stLength = sizeof(stServerReturnCgysManagerCmd);

			subtype = 0;
			index = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置


		// 联合结构体
#ifdef _union_struct
#if e_msg_cgys_create
		_cgys_return_status_info		data;
#elif e_msg_cgys_loading
		_cgys_return_status_info		data;
#elif e_msg_cgys_unloading
		_cgys_return_status_info		data;
#elif e_msg_cgys_chargeback
		_cgys_return_status_info		data;
#elif e_msg_cgys_destroy
		_cgys_return_status_info		data;
#elif e_msg_cgys_view_all
		int32_t							count;
		_cgys_return_data_view_info		data;
#elif e_msg_cgys_view_uid
		int32_t							count;
		_cgys_return_data_view_info		data;
#elif e_msg_cgys_view_tid
		int32_t							count;
		_cgys_return_data_view_info		data;
#endif
#endif
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 采购运输 借/还款
	struct _cgys_jk_submit_document
	{
		_cgys_jk_submit_document()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_document));
			return;
		};

		int64_t			sn;					// 保留 (借款 UID)
		int64_t			a_sn;				// 保留 (账户 UID)
		int32_t			autoratify;			// 自动审批 (预留)
		wchar_t			name[64];			// 借款人
		wchar_t			purpose[120];		// 事由/用途
		float_t			amount;				// 借款金额
		wchar_t			method[10];			// 收款方式
		wchar_t			card[30];			// 卡号
		wchar_t			notes[200];			// 备注
	};

	struct _cgys_jk_submit_ratify
	{
		_cgys_jk_submit_ratify()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_ratify));
			return;
		};

		int64_t			sn;					// 借款 UID
		int32_t			ratify;				// 审批, 1=同意 0=拒绝
	};

	struct _cgys_jk_submit_overy
	{
		_cgys_jk_submit_overy()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_overy));
			return;
		};

		int64_t			sn;					// 借款 UID
		wchar_t			name[64];			// 收款人
		float_t			amount;				// 收款金额
		wchar_t			method[10];			// 收款方式
		wchar_t			card[30];			// 卡号
	};

	struct _cgys_jk_submit_chargeback
	{
		_cgys_jk_submit_chargeback()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_chargeback));
			return;
		};

		int64_t			sn;					// 借款 UID
	};

	struct _cgys_jk_submit_view_all
	{
		_cgys_jk_submit_view_all()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_view_all));

			timeend.reset();
			timebegin.reset();
			return;
		};

		int32_t			mode;			// 0=无,1=状态,2=时间,3=状态+时间
		int32_t			pageindex;		// 页码 (>0)
		int32_t			pagenumber;		// 数量 (>5 && <100)
		int32_t			status;			// 参考 _cgys_return_data_view_info
		TIMESTAMP		timebegin;		// 起始时间
		TIMESTAMP		timeend;		// 结束时间
	};

	struct _cgys_jk_submit_view_name
	{
		_cgys_jk_submit_view_name()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_view_name));

			timeend.reset();
			timebegin.reset();
			return;
		};

		wchar_t			name[64];		// 借款人
		int32_t			mode;			// 0=无,1=状态,2=时间,3=状态+时间
		int32_t			pageindex;		// 页码 (>0)
		int32_t			pagenumber;		// 数量 (>5 && <100)
		int32_t			status;			// 参考 _cgys_return_data_view_info
		TIMESTAMP		timebegin;		// 起始时间
		TIMESTAMP		timeend;		// 结束时间
	};

	struct _cgys_jk_submit_view_sn
	{
		_cgys_jk_submit_view_sn()
		{
			memset(this, 0, sizeof(_cgys_jk_submit_view_sn));
			return;
		};

		int64_t			sn;					// 借款 UID
	};

	// 请求结构
	struct stUserRequestCgysDebtManagerCmd : public Msg
	{
		stUserRequestCgysDebtManagerCmd()
		{
			dwType = USER_REQUEST_CGYS_DEBT_PARA;
			stLength = sizeof(stUserRequestCgysDebtManagerCmd);

			subtype = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置

		// 联合结构体
#ifdef _union_struct
#if e_msg_cgys_jk_create
		_cgys_jk_submit_document		data;
#elif e_msg_cgys_jk_ratify
		_cgys_jk_submit_ratify			data;
#elif e_msg_cgys_jk_overy
		_cgys_jk_submit_overy			data;
#elif e_msg_cgys_jk_chargeback
		_cgys_jk_submit_chargeback		data;
#elif e_msg_cgys_jk_view_all
		_cgys_jk_submit_view_all		data;
#elif e_msg_cgys_jk_view_name
		_cgys_jk_submit_view_name		data;
#elif e_msg_cgys_jk_view_uid
		_cgys_jk_submit_view_sn			data;
#endif
#endif		
	};

	// 采购运输 借款 反馈
	struct _cgys_jk_return_status_info
	{
		_cgys_jk_return_status_info()
		{
			memset(this, 0, sizeof(_cgys_jk_return_status_info));
		};

		bool_t				state;		// 状态 1=成功 0=失败
		int32_t				errcode;	// 错误代码
		wchar_t				text[128];	// 附加字符串
	};

	struct _cgys_jk_return_data_view_info
	{
		_cgys_jk_return_data_view_info()
		{
			memset(this, 0, sizeof(_cgys_jk_return_data_view_info));
			return;
		};

		int64_t			sn;					// UID			采购单
		int64_t			link_sn;			// UID			关联信息
		int64_t			a_sn;				// UID			账户
		int32_t			status;				// 状态			0=停用/退单;1=借款申请;2=同意;3=拒绝;4=还款完成
		wchar_t			name[64];			// 借款人
		wchar_t			purpose[120];		// 用途/事由	
		float_t			amount;				// 借款金额
		wchar_t			method1[32];		// 借款方式
		wchar_t			card1[10];			// 卡号
		wchar_t			notes[200];			// 备注
		TIMESTAMP		createtime;			// 借款时间

		wchar_t			method2[32];		// 还款方式
		wchar_t			nickname[32];		// 收款名称
		wchar_t			card2[10];			// 收款卡号
		float_t			amount2;			// 收款金额
		TIMESTAMP		closetime;			// 还款时间
	};

	struct stServerReturnCgysDebtManagerCmd : public Msg
	{
		stServerReturnCgysDebtManagerCmd()
		{
			dwType = RETURN_USER_CGYS_DEBT_MSG;
			stLength = sizeof(stServerReturnCgysDebtManagerCmd);

			subtype = 0;
			index = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置

		// 联合结构体
#ifdef _union_struct
#if	  e_msg_cgys_jk_status
		_cgys_jk_return_status_info		data;
#elif e_msg_cgys_jk_create
		_cgys_jk_submit_document		data;
#elif e_msg_cgys_jk_ratify
		_cgys_jk_submit_ratify			data;
#elif e_msg_cgys_jk_overy
		_cgys_jk_submit_overy			data;
#elif e_msg_cgys_jk_chargeback
		_cgys_jk_submit_chargeback		data;
#elif e_msg_cgys_jk_view_all
		_cgys_jk_submit_view_all		data;
#elif e_msg_cgys_jk_view_name
		_cgys_jk_submit_view_name		data;
#elif e_msg_cgys_jk_view_uid
		_cgys_jk_submit_view_sn			data;
#endif
#endif
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// 采购运输 报销
	struct _cgys_bx_submit_document
	{
		_cgys_bx_submit_document()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_document));
			return;
		};

		int64_t			sn;					// 保留 (借款 UID)
		int64_t			a_sn;				// 保留 (账户 UID)
		int32_t			autoratify;			// 自动审批 (预留)
		wchar_t			name[64];			// 报销人
		wchar_t			method[10];			// 类目
		wchar_t			excerpt[30];		// 摘要
		float_t			amount;				// 金额
		wchar_t			notes[200];			// 备注
	};

	struct _cgys_bx_submit_ratify
	{
		_cgys_bx_submit_ratify()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_ratify));
			return;
		};

		int64_t			sn;					// 借款 UID
		int32_t			ratify;				// 审批, 1=同意 0=拒绝
	};

	struct _cgys_bx_submit_chargeback
	{
		_cgys_bx_submit_chargeback()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_chargeback));
			return;
		};

		int64_t			sn;					// 借款 UID
	};

	struct _cgys_bx_submit_view_all
	{
		_cgys_bx_submit_view_all()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_view_all));

			timeend.reset();
			timebegin.reset();
			return;
		};

		int32_t			mode;			// 0=无,1=状态,2=时间,3=状态+时间
		int32_t			pageindex;		// 页码 (>0)
		int32_t			pagenumber;		// 数量 (>5 && <100)
		int32_t			status;			// 参考 _cgys_return_data_view_info
		TIMESTAMP		timebegin;		// 起始时间
		TIMESTAMP		timeend;		// 结束时间
	};

	struct _cgys_bx_submit_view_name
	{
		_cgys_bx_submit_view_name()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_view_name));

			timeend.reset();
			timebegin.reset();
			return;
		};

		wchar_t			name[64];		// 报销人
		int32_t			mode;			// 0=无,1=状态,2=时间,3=状态+时间
		int32_t			pageindex;		// 页码 (>0)
		int32_t			pagenumber;		// 数量 (>5 && <100)
		int32_t			status;			// 参考 _cgys_return_data_view_info
		TIMESTAMP		timebegin;		// 起始时间
		TIMESTAMP		timeend;		// 结束时间
	};

	struct _cgys_bx_submit_view_sn
	{
		_cgys_bx_submit_view_sn()
		{
			memset(this, 0, sizeof(_cgys_bx_submit_view_sn));
			return;
		};

		int64_t			sn;					// 借款 UID
	};

	// 请求结构
	struct stUserRequestCgysRoutineManagerCmd : public Msg
	{
		stUserRequestCgysRoutineManagerCmd()
		{
			dwType = USER_REQUEST_CGYS_ROUTINE_PARA;
			stLength = sizeof(stUserRequestCgysRoutineManagerCmd);

			subtype = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置

		// 联合结构体
#ifdef _union_struct
#if e_msg_cgys_bx_create
		_cgys_bx_submit_document		data;
#elif e_msg_cgys_bx_ratify
		_cgys_bx_submit_ratify			data;
#elif e_msg_cgys_bx_chargeback
		_cgys_bx_submit_chargeback		data;
#elif e_msg_cgys_bx_view_all
		_cgys_bx_submit_view_all		data;
#elif e_msg_cgys_bx_view_name
		_cgys_bx_submit_view_name		data;
#elif e_msg_cgys_bx_view_uid
		_cgys_bx_submit_view_sn			data;
#endif
#endif		
	};

	// 采购运输 报销 反馈
	struct _cgys_bx_return_status_info
	{
		_cgys_bx_return_status_info()
		{
			memset(this, 0, sizeof(_cgys_bx_return_status_info));
		};

		bool_t				state;		// 状态 1=成功 0=失败
		int32_t				errcode;	// 错误代码
		wchar_t				text[128];	// 附加字符串
	};

	struct _cgys_bx_return_data_view_info
	{
		_cgys_bx_return_data_view_info()
		{
			memset(this, 0, sizeof(_cgys_bx_return_data_view_info));
			return;
		};

		int64_t			sn;					// UID			采购单
		int64_t			a_sn;				// UID			账户
		int32_t			status;				// 状态			0=停用/退单;1=报销申请;2=同意;3=拒绝;
		wchar_t			name[64];			// 报销人
		wchar_t			method[20];			// 类目
		wchar_t			excerpt[30];		// 摘要	
		float_t			amount;				// 金额
		wchar_t			notes[200];			// 备注
		TIMESTAMP		createtime;			// 借款时间
		TIMESTAMP		closetime;			// 审批时间
	};

	struct stServerReturnCgysRoutineManagerCmd : public Msg
	{
		stServerReturnCgysRoutineManagerCmd()
		{
			dwType = RETURN_USER_CGYS_ROUTINE_MSG;
			stLength = sizeof(stServerReturnCgysRoutineManagerCmd);

			subtype = 0;
			index = 0;
			return;
		};

		int16_t							subtype;			// 控制码
		uint32_t						index;				// 位置

		// 联合结构体
#ifdef _union_struct
#if	  e_msg_cgys_bx_status
		_cgys_bx_return_status_info		data;
#elif e_msg_cgys_bx_create
		_cgys_bx_submit_document		data;
#elif e_msg_cgys_bx_ratify
		_cgys_bx_submit_ratify			data;
#elif e_msg_cgys_bx_chargeback
		_cgys_bx_submit_chargeback		data;
#elif e_msg_cgys_bx_view_all
		_cgys_bx_submit_view_all		data;
#elif e_msg_cgys_bx_view_name
		_cgys_bx_submit_view_name		data;
#elif e_msg_cgys_bx_view_uid
		_cgys_bx_submit_view_sn			data;
#endif
#endif
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
#define CheckUserSysAuth(n)			GetValueBit(m_user_info.r_xtgl, n)
	
	// 采购运输
	enum EnumCaiGouYunShuAuth
	{
		AUTH_CGYS_R,			// 采购运输 查看
		AUTH_CGYS_W,			// 采购运输 使用
		AUTH_CGYS_JK_R,			// 采购运输 借/还款 查看
		AUTH_CGYS_JK_W,			// 采购运输 借/还款 使用
		AUTH_CGYS_BX_R,			// 采购运输 报销 查看
		AUTH_CGYS_BX_W,			// 采购运输 报销 使用
	};
#define CheckUserCgysAuth(n)			GetValueBit(m_user_info.r_cgys, n)

	KyushuEventEnd
};