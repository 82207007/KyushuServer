<<<<<<< Updated upstream
#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KyushuServer
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Ö÷°üÀàĞÍ
	enum KyushuMsgType
	{
		RETURN_USER_FAIL_MSG		= 1002,		// Ê§°ÜÏûÏ¢
	
		USER_REQUEST_LOGIN_PARA,				// ÇëÇóµÇÂ¼
		RETURN_USER_LOGIN_MSG,					// µÇÂ¼·´À¡

		USER_REQUEST_VIEW_ROLE_PARA,			// ä¯ÀÀ½ÇÉ«
		RETURN_USER_REQ_VIEW_ROLE_MSG,			// ·´À¡½ÇÉ«ÁĞ±í

		USER_REQUEST_REG_ACCOUNT_PARA,			// ×¢²áÕË»§
		RETURN_USER_REG_ACCOUNT_MSG,			// ×¢²á·´À¡

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ×Ó°üÀàĞÍ
	enum KyushuSubMsgType
	{
		// µÇÂ¼·½Ê½
		e_msg_account_login_mode	= 10001,	// ÕË»§ÃÜÂë
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ÏûÏ¢µÈ¼¶
	enum enumMsgLevel
	{
		level_high		= 0,					// ¸ß
		level_normal,							// ÖĞ
		level_low								// µÍ
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Ñ¹Ëõ±êÖ¾
	enum enumMsgFlag
	{
		msgflag_normal		= 0,				// ÆÕÍ¨±êÖ¾
		msgflag_compress	= 0x01,				// Ñ¹Ëõ±êÖ¾
		msgflag_encrypt		= 0x01 << 1,		// ¼ÓÃÜ±êÖ¾
	};
#pragma pack(push, 1)

	////////////////////////////////////////////////////////////////////////////////////////////////
	enum EKyushuErrorCode
	{
		EKEC_BEGIN					= 10001,

		EKEC_RECV_SIZE_ABNORMAL,				// Êı¾İÁ÷³ß´çÒì³£, ·Ç·¨Êı¾İ»ò³ß´ç
		EKEC_RECV_STREAM_ABNORMAL,				// Êı¾İÁ÷½âÑ¹Ê§°Ü, ·ÇÆ¥ÅäµÄÑ¹Ëõ·½Ê½»ò·¢ËÍÊı¾İ³¬³ö½âÑ¹³ß´çÉÏÏŞ

		EKEC_LOGIN_ACCOUNT,						// ÕË»§
		EKEC_LOGIN_PASSWORD,					// ÃÜÂë
		EKEC_LOGIN_MODE,						// µÇÂ¼Ä£Ê½Òì³£
		EKEC_LOGIN_WAIT,						// ÖØ¸´ÇëÇó (ÒÑ¾­Ìá½»µÇÂ¼ÇëÇó»òÕıÔÚ´¦ÀíÖĞ)
		EKEC_LOGIN_STATE_ABNORMAL,				// µ±Ç°×´Ì¬Òì³£ (²»·ûºÏµÇÂ¼×´Ì¬, ÓĞÒì³£Êı¾İ°üµ¼ÖÂÁ¬½ÓÒì³£)
		EKEC_LOGIN_DB_FAIL,						// ÇëÇóÊ§°Ü (DB)
		EKEC_LOGIN_FAIL,						// µÇÂ¼Ê§°Ü
		EKEC_LOGIN_TIME_OUT,					// µÇÂ¼³¬Ê± (Á¬½ÓºóÒ»¶¨Ê±¼äÄÚÎ´½øĞĞµÇÂ¼²Ù×÷)

		EKEC_LOGIN_NOT_STREAM,					// Ã»ÓĞµÇÂ¼½øĞĞ´«Êä·Ç·¨Êı¾İ°ü
		EKEC_AUTH_NOT,							// Ã»ÓĞÈ¨ÏŞ

		EKEC_VIEW_ROLE_LIST_NOT,				// ²é¿´ÁĞ±íÒì³£ (ÍøÂçÒì³£»òÊı¾İ¿â²éÑ¯Ê§°Ü)

	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// »ù´¡½á¹¹
	struct MsgCommonHeader
	{
		uint32_t	stLength;					// ĞÅÏ¢³¤¶È
		char_t		cMsgFlag;					// ĞÅÏ¢±êÖ¾
	};

	struct MsgHeader : public MsgCommonHeader
	{
		MsgHeader()
		{
			dwType = 0;
			uMsgLevel = level_high;
			cMsgFlag = msgflag_normal;
		};

		int16_t		dwType;						// ÏûÏ¢ÀàĞÍ
		char_t		uMsgLevel;					// ÏûÏ¢µÈ¼¶
	};

	struct Msg : public MsgHeader
	{
		int32_t		GetType() { return dwType; }
		uint32_t	GetLength() { return stLength; }
		int32_t		GetLevel() { return static_cast<int32_t>(uMsgLevel); }
		void_t		SetLevel(enumMsgLevel lev) { uMsgLevel = static_cast<char_t>(lev); }
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// Ê§°Ü´íÎó
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

		char_t		text[128];					// ÄÚÈİ
		int32_t		byType;						// ´íÎó´úÂë
		uint8_t		byReturn;					// 0 = Ê§°Ü, 1 = ³É¹¦
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ÕË»§µÇÂ¼
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

		int16_t			subtype;				// 10001 = ÆÕÍ¨µÇÂ¼
		char_t			name[33];				// ÕË»§
		char_t			password[65];			// ÃÜÂë
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// µÇÂ¼³É¹¦
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

		int64_t			uid;					// ÕË»§UID
		char_t			nickname[65];			// Ãû³Æ
		char_t			rolename[33];			// ½ÇÉ«·Ö×éÃû
		int64_t			cgys;					// È¨ÏŞ ²É¹ºÔÊĞí ³¤ÕûÊı 64Î»¿ØÖÆ64¸öÈ¨ÏŞ
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ²é¿´½ÇÉ«
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
	// ·´À¡½ÇÉ«ĞÅÏ¢
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
		char_t		name[32];			// ½ÇÉ«·Ö×éÃû
		int64_t		xtgl;				// È¨ÏŞ ÏµÍ³¹ÜÀí
		int64_t		cgys;				// È¨ÏŞ ²É¹ºÔËÊä
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

		int16_t				subtype;	// ×ÓÀàĞÍ
		uint32_t			index;		// Î»ÖÃ
		int32_t				count;		// Êı¾İÊıÁ¿ (Èç¹û¿ÉÄÜÔòÎªÊµ¼ÊÊıÁ¿, ´ËÖµ¿ÉÄÜÎª¿Õ)
		_view_role_info*	dataarray;	// Êı¾İÊµÌå
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ´´½¨½ÇÉ«
	struct stUserRequestRegRoleCmd : public Msg
	{
		stUserRequestRegRoleCmd()
		{

		};


	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ´´½¨ÕË»§·´À¡
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

		int16_t			state;					// 0=Ê§°Ü 1=³É¹¦
		int64_t			uid;					// UID
		char_t			username[32];			// ÕË»§
		char_t			nickname[64];			// ĞÕÃû
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// È¨ÏŞ¼ì²é
#define CheckAuthority(num, n)			GetValueBit(num, n)

	// ÏµÍ³È¨ÏŞ
	enum EnumSystemAuth
	{
		AUTH_SYS_SETTINGS,			// ÏµÍ³ÉèÖÃ
		AUTH_SYS_ROLE,				// ½ÇÉ«ÉèÖÃ
		AUTH_SYS_ACCOUNT,			// ²Ù×÷Ô±ÉèÖÃ
	};
#define CheckUserSysAuth(n)				GetValueBit(m_user_info.r_xtgl, n)


#pragma pack(pop)
=======
ï»¿#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace KyushuServer
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// ä¸»åŒ…ç±»å‹
	enum KyushuMsgType
	{
		RETURN_USER_FAIL_MSG		= 1002,		// å¤±è´¥æ¶ˆæ¯
	
		USER_REQUEST_LOGIN_PARA,				// è¯·æ±‚ç™»å½•
		RETURN_USER_LOGIN_MSG,					// ç™»å½•åé¦ˆ

		USER_REQUEST_VIEW_ROLE_PARA,			// æµè§ˆè§’è‰²
		RETURN_USER_REQ_VIEW_ROLE_MSG,			// åé¦ˆè§’è‰²åˆ—è¡¨

		USER_REQUSET_SET_ROLE_PARA,				// è®¾ç½®è§’è‰² (æ·»åŠ ã€æ›´æ–°ã€åˆ é™¤)

		USER_REQUEST_REG_ACCOUNT_PARA,			// æ³¨å†Œè´¦æˆ·
		RETURN_USER_REG_ACCOUNT_MSG,			// æ³¨å†Œåé¦ˆ

		MSG_END
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// å­åŒ…ç±»å‹
	enum KyushuSubMsgType
	{
		// ç™»å½•æ–¹å¼
		e_msg_account_login_mode	= 10001,	// è´¦æˆ·å¯†ç 

		// è§’è‰²
		e_msg_role_add,
		e_msg_role_update,
		e_msg_role_delete,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// æ¶ˆæ¯ç­‰çº§
	enum enumMsgLevel
	{
		level_high		= 0,					// é«˜
		level_normal,							// ä¸­
		level_low								// ä½
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// å‹ç¼©æ ‡å¿—
	enum enumMsgFlag
	{
		msgflag_normal		= 0,				// æ™®é€šæ ‡å¿—
		msgflag_compress	= 0x01,				// å‹ç¼©æ ‡å¿—
		msgflag_encrypt		= 0x01 << 1,		// åŠ å¯†æ ‡å¿—
	};
#pragma pack(push, 1)

	////////////////////////////////////////////////////////////////////////////////////////////////
	enum EKyushuErrorCode
	{
		EKEC_BEGIN					= 10001,

		EKEC_RECV_SIZE_ABNORMAL,				// æ•°æ®æµå°ºå¯¸å¼‚å¸¸, éæ³•æ•°æ®æˆ–å°ºå¯¸
		EKEC_RECV_STREAM_ABNORMAL,				// æ•°æ®æµè§£å‹å¤±è´¥, éåŒ¹é…çš„å‹ç¼©æ–¹å¼æˆ–å‘é€æ•°æ®è¶…å‡ºè§£å‹å°ºå¯¸ä¸Šé™

		EKEC_LOGIN_ACCOUNT,						// è´¦æˆ·
		EKEC_LOGIN_PASSWORD,					// å¯†ç 
		EKEC_LOGIN_MODE,						// ç™»å½•æ¨¡å¼å¼‚å¸¸
		EKEC_LOGIN_WAIT,						// é‡å¤è¯·æ±‚ (å·²ç»æäº¤ç™»å½•è¯·æ±‚æˆ–æ­£åœ¨å¤„ç†ä¸­)
		EKEC_LOGIN_STATE_ABNORMAL,				// å½“å‰çŠ¶æ€å¼‚å¸¸ (ä¸ç¬¦åˆç™»å½•çŠ¶æ€, æœ‰å¼‚å¸¸æ•°æ®åŒ…å¯¼è‡´è¿æ¥å¼‚å¸¸)
		EKEC_LOGIN_DB_FAIL,						// è¯·æ±‚å¤±è´¥ (DB)
		EKEC_LOGIN_FAIL,						// ç™»å½•å¤±è´¥
		EKEC_LOGIN_TIME_OUT,					// ç™»å½•è¶…æ—¶ (è¿æ¥åä¸€å®šæ—¶é—´å†…æœªè¿›è¡Œç™»å½•æ“ä½œ)

		EKEC_LOGIN_NOT_STREAM,					// æ²¡æœ‰ç™»å½•è¿›è¡Œä¼ è¾“éæ³•æ•°æ®åŒ…
		EKEC_AUTH_NOT,							// æ²¡æœ‰æƒé™

		EKEC_UID_FAIL,							// UID å¼‚å¸¸
		EKEC_NAME_LEN_FAIL,						// åç§°å°ºå¯¸ä¸æ­£ç¡®

		EKEC_VIEW_ROLE_LIST_NOT,				// æŸ¥çœ‹åˆ—è¡¨å¼‚å¸¸ (ç½‘ç»œå¼‚å¸¸æˆ–æ•°æ®åº“æŸ¥è¯¢å¤±è´¥)
		EKEC_SET_ROLE_INFO_FAIL,				// è®¾ç½®è§’è‰²ä¿¡æ¯æ•°æ®å¼‚å¸¸ (éæ³•çš„æäº¤ç±»å‹)

	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// åŸºç¡€ç»“æ„
	struct MsgCommonHeader
	{
		uint32_t	stLength;					// ä¿¡æ¯é•¿åº¦
		char_t		cMsgFlag;					// ä¿¡æ¯æ ‡å¿—
	};

	struct MsgHeader : public MsgCommonHeader
	{
		MsgHeader()
		{
			dwType = 0;
			uMsgLevel = level_high;
			cMsgFlag = msgflag_normal;
		};

		int16_t		dwType;						// æ¶ˆæ¯ç±»å‹
		char_t		uMsgLevel;					// æ¶ˆæ¯ç­‰çº§
	};

	struct Msg : public MsgHeader
	{
		int32_t		GetType() { return dwType; }
		uint32_t	GetLength() { return stLength; }
		int32_t		GetLevel() { return static_cast<int32_t>(uMsgLevel); }
		void_t		SetLevel(enumMsgLevel lev) { uMsgLevel = static_cast<char_t>(lev); }
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	// å¤±è´¥é”™è¯¯
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

		wchar_t		text[128];					// å†…å®¹
		int32_t		byType;						// é”™è¯¯ä»£ç 
		uint8_t		byReturn;					// 0 = å¤±è´¥, 1 = æˆåŠŸ
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// è´¦æˆ·ç™»å½•
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

		int16_t			subtype;				// 10001 = æ™®é€šç™»å½•
		wchar_t			name[32];				// è´¦æˆ·
		wchar_t			password[64];			// å¯†ç 
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ç™»å½•æˆåŠŸ
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

		int64_t			uid;					// è´¦æˆ·UID
		wchar_t			nickname[64];			// åç§°
		wchar_t			rolename[32];			// è§’è‰²åˆ†ç»„å
		int64_t			xtgl;					// æƒé™ ç³»ç»Ÿç®¡ç†
		int64_t			cgys;					// æƒé™ é‡‡è´­å…è®¸ é•¿æ•´æ•° 64ä½æ§åˆ¶64ä¸ªæƒé™
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// æŸ¥çœ‹è§’è‰²
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
	// åé¦ˆè§’è‰²ä¿¡æ¯
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
		wchar_t		name[32];			// è§’è‰²åˆ†ç»„å
		int64_t		xtgl;				// æƒé™ ç³»ç»Ÿç®¡ç†
		int64_t		cgys;				// æƒé™ é‡‡è´­è¿è¾“
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

		int16_t				subtype;	// å­ç±»å‹
		uint32_t			index;		// ä½ç½®
		int32_t				count;		// æ•°æ®æ•°é‡ (å¦‚æœå¯èƒ½åˆ™ä¸ºå®é™…æ•°é‡, æ­¤å€¼å¯èƒ½ä¸ºç©º)
		_view_role_info*	dataarray;	// æ•°æ®å®ä½“
	};

	////////////////////////////////////////////////////////////////////////////////////////////////
	// è®¾ç½®è§’è‰² (æ·»åŠ ã€æ›´æ–°ã€åˆ é™¤)
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
	// åˆ›å»ºè´¦æˆ·åé¦ˆ
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

		int16_t			state;					// 0=å¤±è´¥ 1=æˆåŠŸ
		int64_t			uid;					// UID
		wchar_t			username[32];			// è´¦æˆ·
		wchar_t			nickname[64];			// å§“å
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	// æƒé™æ£€æŸ¥
	// æ¯ç§æƒé™å…±è®¡64ä½æ§åˆ¶å™¨ (å ç”¨8å­—èŠ‚), æ¯ä¸€ä½ä»£è¡¨ä¸€ä¸ªä¸åŒçš„æƒé™ã€‚0=å…³é—­ 1=æ­£å¸¸
#define CheckAuthority(num, n)			GetValueBit(num, n)

	// ç³»ç»Ÿæƒé™
	enum EnumSystemAuth
	{
		AUTH_SYS_SETTINGS,			// ç³»ç»Ÿè®¾ç½®
		AUTH_SYS_ROLE,				// è§’è‰²è®¾ç½®
		AUTH_SYS_ACCOUNT,			// æ“ä½œå‘˜è®¾ç½®
	};
#define CheckUserSysAuth(n)				GetValueBit(m_user_info.r_xtgl, n)


#pragma pack(pop)
>>>>>>> Stashed changes
};