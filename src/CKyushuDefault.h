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

		USER_REQUEST_CGYS_SQD_PARA,				// 采购运输 申请单
		RETURN_USER_CGYS_SQD_MSG,				// 采购运输 申请单反馈

		USER_REQUEST_CGYS_SQD_VIEW_PARA,		// 采购运输 申请单 查询
		RETURN_USER_CGYS_SQD_VIEW_MSG,			// 采购运输 申请单 查询反馈

		USER_REQUEST_CGYS_CGY_PARA,				// 采购运输 驾驶员
		RETURN_USER_CGYS_CGY_MSG,				// 采购运输 驾驶员 操作反馈

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

		// 账户
		e_msg_account_add,
		e_msg_account_update,
		e_msg_account_update2,
		e_msg_account_delete,

		// 数据为空
		e_msg_data_null,			// 浏览查询时数据为空 (已经到尾记录)

		// 申请单 全部查询
		e_msg_cgys_sqd_view_item_list,		// 查询 采购单 详细信息

		e_msg_cgys_sqd_view_all,			// 全部查询模式
		e_msg_cgys_sqd_view_sn,				// 精确查找 UID
		e_msg_cgys_sqd_view_invoicenumber,	// 精确查找 票号
		e_msg_cgys_sqd_view_ghs,			// 模糊查找 供货商
		e_msg_cgys_sqd_view_sqr,			// 模糊查找 申请人
		e_msg_cgys_sqd_view_jsy,			// 模糊查找 采购人/驾驶员


		e_msg_cgys_cgy_new,					// 采购运输 驾驶员 接单
		e_msg_cgys_cgy_delete,				// 采购运输 驾驶员 退单
		e_msg_cgys_cgy_begin,				// 采购运输 驾驶员 装货
		e_msg_cgys_cgy_end,					// 采购运输 驾驶员 卸货
		
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
		EKEC_DATA_SERVER_BUSY,					// 数据服务器网络繁忙，重新请求即可。
		EKEC_TIME_INVALID,						// 未知的时间格式

		EKEC_LOAD_GPS_INFO_FAIL,				// 加载缓冲区失败
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

		EKEC2_UID_TICKET_EXISTS,	// 单据号或票号已存在
		EKEC2_COMMIT_DATA_NULL,		// 提交数据为空 (申请单内容为空)
		EKEC2_ADDDATE_FAIL,			// 添加数据失败
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
	// 采购运输 申请单
	struct _sqd_item_info
	{
		_sqd_item_info()
		{
			spsl = 0;
			spjj = 0; spje = 0;
			memset(spm, 0, sizeof(spm));
			memset(spgg, 0, sizeof(spgg));
			memset(spdw, 0, sizeof(spdw));
			memset(spbz, 0, sizeof(spbz));
			memset(sptm, 0, sizeof(sptm));
			return;
		};

		wchar_t			spm[60];	// 名称			(>0)
		wchar_t			spgg[30];	// 规格			(>0)
		int32_t			spsl;		// 数量
		wchar_t			spdw[10];	// 单位			(>0)
		float_t			spjj;		// 进价/单价
		float_t			spje;		// 金额/总价
		wchar_t			spbz[120];	// 备注
		wchar_t			sptm[120];	// 条形码
	};

	struct stUserRequestCgysSqdCmd : public Msg
	{
		stUserRequestCgysSqdCmd()
		{
			dwType = USER_REQUEST_CGYS_SQD_PARA;
			stLength = sizeof(stUserRequestCgysSqdCmd);

			subtype = 0;
			count = 0;
			memset(ticketnumber, 0, sizeof(ticketnumber));
			memset(ghs, 0, sizeof(ghs));
			memset(sqr, 0, sizeof(sqr));
			memset(jhrq, 0, sizeof(jhrq));
			return;
		};

		int16_t				subtype;			// 
		wchar_t				ticketnumber[30];	// 票号				(>5)
		wchar_t				ghs[120];			// 供货商			(>3)
		wchar_t				sqr[64];			// 申请人 (采购员)	(>2)
		wchar_t				jhrq[40];			// 交付日期			(>7) (2020-01-01 00:00:00)
		int32_t				count;				// 商品信息数量	(实际提交数据数量: <=8 or >=1)
		_sqd_item_info*		pItemInfo;			// 商品信息		(该数据尺寸必须严格对齐8条,如果只有1条其他7条全传0。)
	};

	// 反馈采购运输 申请单状态
	struct stServerReturnCgysSqdCmd : public Msg
	{
		stServerReturnCgysSqdCmd()
		{
			dwType = RETURN_USER_CGYS_SQD_MSG;
			stLength = sizeof(stServerReturnCgysSqdCmd);

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
	// 采购运输 申请单 查询
	struct _cgys_sqd_view_all
	{
		_cgys_sqd_view_all()
		{
			pageindex = 0;
			number = 0;
			return;
		};

		int32_t				pageindex;			// 页码索引
		int32_t				number;				// 显示数量
		bool_t				usetimemode;		// 启用时间范围查找模式
		wchar_t				begintime[40];		// 时间范围		(2020-01-01 00:00:00)
		wchar_t				endtime[40];		// 结束时间		(2020-01-01 00:00:00)
	};

	struct _cgys_sqd_view_sn
	{
		_cgys_sqd_view_sn()
		{
			sn = 0;
			return;
		};

		int64_t				sn;					// 申请单 UID
	};

	struct _cgys_sqd_view_invoicenumber
	{
		_cgys_sqd_view_invoicenumber()
		{
			memset(ticketnumber, 0, sizeof(ticketnumber));
			return;
		};

		wchar_t				ticketnumber[30];	// 票号				(>5)
	};

	struct _cgys_sqd_view_ghs
	{
		_cgys_sqd_view_ghs()
		{
			usetimemode = false;
			memset(ghs, 0, sizeof(ghs));
			memset(begintime, 0, sizeof(begintime));
			memset(endtime, 0, sizeof(endtime));
			return;
		};

		wchar_t				ghs[120];			// 供货商		(>3)
		bool_t				usetimemode;		// 启用时间范围查找模式
		wchar_t				begintime[40];		// 时间范围		(2020-01-01 00:00:00)
		wchar_t				endtime[40];		// 结束时间		(2020-01-01 00:00:00)
	};

	struct _cgys_sqd_view_sqr
	{
		_cgys_sqd_view_sqr()
		{
			usetimemode = false;
			memset(sqr, 0, sizeof(sqr));
			memset(begintime, 0, sizeof(begintime));
			memset(endtime, 0, sizeof(endtime));
			return;
		};

		wchar_t				sqr[64];			// 申请人		(>2)
		bool_t				usetimemode;		// 启用时间范围查找模式
		wchar_t				begintime[40];		// 时间范围		(2020-01-01 00:00:00)
		wchar_t				endtime[40];		// 结束时间		(2020-01-01 00:00:00)
	};

	struct _cgys_sqd_view_jsy
	{
		_cgys_sqd_view_jsy()
		{
			usetimemode = false;
			memset(jsy, 0, sizeof(jsy));
			memset(begintime, 0, sizeof(begintime));
			memset(endtime, 0, sizeof(endtime));
			return;
		};

		wchar_t				jsy[64];			// 采购员/驾驶员	(>7)
		bool_t				usetimemode;		// 启用时间范围查找模式
		wchar_t				begintime[40];		// 时间范围		(2020-01-01 00:00:00)
		wchar_t				endtime[40];		// 结束时间		(2020-01-01 00:00:00)
	};

	struct _cgys_sqd_view_item_list
	{
		/*
		struct _cgys_sqd_view_sn_list_info
		{
			_cgys_sqd_view_sn_list_info()
			{

			};

			wchar_t						name[60];		// 名称
			wchar_t						norms[30];		// 规格
			int32_t						number;			// 数量
			wchar_t						unit[10];		// 单位
			float_t						monovalent;		// 单价
			float_t						total;			// 总价
			wchar_t						notes[120];		// 备注
			wchar_t						barcode[120];	// 预留 (条形码)
		};
		*/

		_cgys_sqd_view_item_list()
		{
			sn = 0;
			return;
		};

		int64_t							sn;
	};


	struct stUserRequestCgysSqdViewCmd : public Msg
	{
		stUserRequestCgysSqdViewCmd()
		{
			dwType = USER_REQUEST_CGYS_SQD_VIEW_PARA;
			stLength = sizeof(stUserRequestCgysSqdViewCmd);

			subtype = 0;
			index = 0;
			return;
		};

		int16_t				subtype;			// 查询类型 0
		uint32_t			index;				// 位置
		
		// 联合结构
#ifdef _view_subtype
#if e_msg_cgys_sqd_view_item_list
		_cgys_sqd_view_sn_list*			data;
#elif e_msg_cgys_sqd_view_all
		_cgys_sqd_view_all*				data;
#elif e_msg_cgys_sqd_view_sn
		_cgys_sqd_view_sn*				data;
#elif e_msg_cgys_sqd_view_invoicenumber
		_cgys_sqd_view_invoicenumber*	data;
#elif e_msg_cgys_sqd_view_ghs
		_cgys_sqd_view_ghs*				data;
#elif e_msg_cgys_sqd_view_sqr
		_cgys_sqd_view_sqr*				data;
#elif e_msg_cgys_sqd_view_jsy
		_cgys_sqd_view_jsy*				data;
#endif
#endif
	};


	// 反馈申请单查询结构
	struct _view_cgys_sqd_list_info
	{
		_view_cgys_sqd_list_info()
		{
			sn = 0;
			tstate = 0; cgy_sn = 0;
			memset(ticketnumber, 0, sizeof(ticketnumber));
			memset(ghs, 0, sizeof(ghs));
			memset(sqr, 0, sizeof(sqr));
			memset(jhrq, 0, sizeof(jhrq));
			memset(createtime, 0, sizeof(createtime));
			return;
		};

		int64_t					sn;					// UID
		int32_t					tstate;				// 状态
		int64_t					cgy_sn;				// 采购员 UID
		wchar_t					ticketnumber[30];	// 票号
		wchar_t					ghs[120];			// 供货商
		wchar_t					sqr[64];			// 申请人 (采购员)
		wchar_t					jhrq[40];			// 交付日期
		wchar_t					createtime[40];		// 创建时间
	};

	struct _view_cgys_sqd_item_info
	{
		_view_cgys_sqd_item_info()
		{
			sn = 0;
			spsl = 0;
			spjj = 0; spje = 0;
			memset(spm, 0, sizeof(spm));
			memset(spgg, 0, sizeof(spgg));
			memset(spdw, 0, sizeof(spdw));
			memset(spbz, 0, sizeof(spbz));
			memset(sptm, 0, sizeof(sptm));
			memset(createtime, 0, sizeof(createtime));
			return;
		};

		int64_t			sn;				// 内码
		wchar_t			spm[60];		// 名称
		wchar_t			spgg[30];		// 规格
		int32_t			spsl;			// 数量
		wchar_t			spdw[10];		// 单位
		float_t			spjj;			// 进价/单价
		float_t			spje;			// 金额/总价
		wchar_t			spbz[120];		// 备注
		wchar_t			sptm[120];		// 条形码
		wchar_t			createtime[40];	// 创建时间
	};

	struct stServerReturnViewCgysSqdCmd : public Msg
	{
		stServerReturnViewCgysSqdCmd()
		{
			dwType = RETURN_USER_CGYS_SQD_VIEW_MSG;
			stLength = sizeof(stServerReturnViewAccountCmd);

			subtype = 0;
			index = 0;
			return;
		};

		int16_t				subtype;	// 子类型	e_msg_data_null 为此值时记录为空或已到尾记录后(可配合count验证)
		uint32_t			index;		// 位置
		int32_t				count;		// 数据数量	(如果可能则为实际数量, 此值可能为空)

		// 联合结构
#ifdef _view_subtype
#if e_msg_cgys_sqd_view_item_list

#elif e_msg_cgys_sqd_view_all
		_view_cgys_sqd_list_info*			dataarray;
#elif e_msg_cgys_sqd_view_sn

#elif e_msg_cgys_sqd_view_invoicenumber

#elif e_msg_cgys_sqd_view_ghs

#elif e_msg_cgys_sqd_view_sqr

#elif e_msg_cgys_sqd_view_jsy

#endif
#endif

	};

	// 反馈采购运输 驾驶员 申请/退单等状态
	struct stServerReturnCgysCgyCmd : public Msg
	{
		stServerReturnCgysCgyCmd()
		{
			dwType = RETURN_USER_CGYS_SQD_MSG;
			stLength = sizeof(stServerReturnCgysCgyCmd);

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
	// 驾驶员接单
	struct _cgys_cgy_new
	{
		_cgys_cgy_new()
		{
			uid_sqd = 0;
			uid_jsy = 0;
			uid_cl = 0;
			memset(notes, 0, sizeof(notes));
			return;
		};

		int64_t			uid_sqd;		// 采购单 SN
		int64_t			uid_jsy;		// 驾驶员 SN
		int64_t			uid_cl;			// 车辆	 SN
		wchar_t			notes[200];		// 备注
	};

	struct _cgys_cgy_delete
	{
		_cgys_cgy_delete()
		{
			uid_cgy = 0;
			return;
		};

		int64_t			uid_cgy;		// 采购单(驾驶员接单) UID
	};

	struct _cgys_cgy_begin
	{
		_cgys_cgy_begin()
		{
			uid_cgy = 0;
			number = 0;
			memset(image1, 0, sizeof(image1));
			memset(image2, 0, sizeof(image2));
			memset(point, 0, sizeof(point));
			memset(gps, 0, sizeof(gps));
			return;
		};

		int64_t			uid_cgy;		// 采购单(驾驶员接单) UID
		wchar_t			image1[120];	// 照片1
		wchar_t			image2[120];	// 照片2
		wchar_t			point[120];		// 地点
		wchar_t			gps[120];		// gps
		int32_t			number;			// 数量
	};

	struct _cgys_cgy_end
	{
		_cgys_cgy_end()
		{
			uid_cgy = 0;
			memset(image1, 0, sizeof(image1));
			memset(image2, 0, sizeof(image2));
			memset(point, 0, sizeof(point));
			memset(gps, 0, sizeof(gps));
			return;
		};

		int64_t			uid_cgy;		// 采购单(驾驶员接单) UID
		wchar_t			image1[120];	// 照片1
		wchar_t			image2[120];	// 照片2
		wchar_t			point[120];		// 地点
		wchar_t			gps[120];		// gps
	};

	struct stUserRequestCgysCgyCmd : public Msg
	{
		stUserRequestCgysCgyCmd()
		{
			dwType = USER_REQUEST_CGYS_CGY_PARA;
			stLength = sizeof(stUserRequestCgysCgyCmd);

			subtype = 0;
			return;
		};

		int16_t				subtype;
		uint32_t			index;		// 位置

		// 联合结构
#ifdef _view_subtype
#if e_msg_cgys_cgy_new
		_cgys_cgy_new*		data;
#elif e_msg_cgys_cgy_delete
		_cgys_cgy_delete*	data;
#elif e_msg_cgys_cgy_begin
		_cgys_cgy_begin*	data;
#elif e_msg_cgys_cgy_end
		_cgys_cgy_end*		data;
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
		AUTH_CGYS_SQD_READ,			// 申请单 查看
		AUTH_CGYS_SQD_USE,			// 申请单 使用 (+查看)
		AUTH_CGYS_CGY_READ,			// 驾驶员 查看
		AUTH_CGYS_CGY_USE,			// 驾驶员 使用 (+查看)
	};
#define CheckUserCgysAuth(n)			GetValueBit(m_user_info.r_cgys, n)

	KyushuEventEnd
};