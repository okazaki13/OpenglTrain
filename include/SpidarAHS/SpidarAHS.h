/** @file
	@JP
		@brief SpidarAHS 関数定義
		@author 赤羽 克仁

		Spidarを利用するためのC++関数API

	@END_JP
	@EN
		@brief SpidarAHS C++ function
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/7/28
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/

#pragma once

#ifdef SPIDARAHS_EXPORTS
#define SPIDARAHS_API __declspec(dllexport)
#else
#define SPIDARAHS_API __declspec(dllimport)
#endif

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidarの識別用ハンドル．<br>
	コントローラ1台に対して1つのハンドルが対応する．<br>
	<b>SPIDAR-Gのとき（8本糸で並進3自由度・回転3自由度）</b><br>
	コントローラ1台に対して1組のSPIDARが実行可能 AHS_SPIDAR_G, ahsCreate_SpidarG()<br>
	<b>SPIDAR-4のとき（4本糸で並進3自由度）</b><br>
	コントローラ1台に対して2組のSPIDARが実行可能 AHS_SPIDAR_4, ahsCreate_Spidar4()<br>
	<b>SPIDAR-Xのとき（8本糸を独立に操作）</b><br>
	コントローラ1台に対して8組のSPIDARが実行可能 AHS_SPIDAR_X, ahsCreate_SpidarX()<br>
@END_JP
@EN
	@brief Spidar handle
@END_EN
*/
typedef HANDLE SPIDAR_HANDLE;



/**
@JP
	@brief 生成するSPIDARタイプ
@END_JP
@EN
	@brief 
@END_EN
*/
enum AhsSpidarTypeEnum{
	AHS_SPIDAR_4,				/**< @JP SPIDAR_4:並進3自由度の4本糸でベーシックなタイプ @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_G,				/**< @JP SPIDAR_G:並進・回転6自由度の8本糸でグリップタイプ @END_JP @EN Dummy. @END_EN*/
	AHS_SH_SPIDAR_G,			/**< @JP SPIDAR_G:並進・回転6自由度の8本糸でグリップタイプのSH版 @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_8,				/**< @JP SPIDAR_8:並進3自由度の3本糸でポインタタイプが8セット（左手4指＋右手4指） @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_X,				/**< @JP SPIDAR_X:ユーザが任意で糸のコントロールをするときに使うタイプ @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_TYPE_ENUM_MAX	/**< @JP 列挙型のサイズ取得のためのダミー @END_JP @EN Dummy. @END_EN*/
};



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidarのためのプログラムの起動と初期化処理．<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0のみ設定可能）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	xmlFileName SPIDARの設定ファイル名(.xml) SPIDARのタイプはxml内で定義(Spidar,Spidar-G)
	@param[in]	isVoice		音声案内（1:有効、0:無効）（省略可）
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		成功した時は0,失敗した時は0以外を返す
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar(SPIDAR_HANDLE* handle,char* xmlFileName,int isVoice = 1, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 【今後廃止（ahsCreate_Spidar(SPIDAR_HANDLE* handle,char* xmlFileName)を使ってください）】<br>
	Spidarのためのプログラムの起動と初期化処理．<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0のみ設定可能）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	type		SPIDARのタイプ(Spidar,Spidar-G)
	@param[in]	xmlFileName SPIDARの設定ファイル名(.xml)
	@param[in]	isVoice		音声案内（1:有効、0:無効）（省略可）
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		成功した時は0,失敗した時は0以外を返す
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar(SPIDAR_HANDLE* handle, AhsSpidarTypeEnum type, char* xmlFileName,int isVoice = 1, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 【今後廃止（ahsCreate_Spidarを使ってください）】<br>
	SpidarG(並進・回転6自由度の8本糸でグリップタイプ)のためのプログラムの起動と初期化処理．<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0のみ設定可能）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	xmlFileName SPIDARの設定ファイル名(.xml)
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		成功した時は0,失敗した時は0以外を返す
@END_EN
*/
SPIDARAHS_API int ahsCreate_SpidarG(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 【今後廃止（ahsCreate_Spidarを使ってください）】<br>
	SPIDAR_8:並進3自由度の3本糸でポインタタイプが8セット（左手4指＋右手4指）<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0のみ設定可能）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	xmlFileName SPIDARの設定ファイル名(.xml)
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		成功した時は0,失敗した時は0以外を返す
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar8(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 【今後廃止（ahsCreate_Spidarを使ってください）】<br>
	Spidar4(並進3自由度の4本糸でベーシックなタイプ)のためのプログラムの起動と初期化処理．<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0もしくは1を設定可能）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	xmlFileName SPIDARの設定ファイル名(.xml)
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize Spidar4
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar4(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 【今後廃止（ahsCreate_Spidarを使ってください）】<br>
	SpidarX(ユーザが任意で糸のコントロールをするときに使うタイプ)のためのプログラムの起動と初期化処理．<br>
	コントローラの電源を投入した順序で当該コントローラのhandleを取得できる．<br>
	（ほかの関数で指定できるspidar_idは0から7までを設定可能）
	（※まだテスト不足）
	@param[out]	handle		起動・初期化したSPIDARのハンドル
	@param[in]	xmlFileName	SPIDARの設定ファイル名(.xml)
	@param[in]	usb_id		取得USB機器のID（省略可・省略推奨）
	@return		成功した時は0,失敗した時は0以外を返す
@END_JP
@EN
	@brief Create and initialize SpidarX
@END_EN
*/
SPIDARAHS_API int ahsCreate_SpidarX(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 力覚提示制御ループの開始<br>
	マルチメディアタイマによる1kHzの更新周波数（設定ファイルにより更新周波数の変更が可能）<br>
	※注意：コントローラ単位（SPIDAR_HANDLE単位）でタイマを起動する必要がある。<br>
	複数台コントローラを接続する場合、コントローラの台数分制御ループが回ることになる。

	@param[in]	handle 対象となるSPIDARのハンドル
@END_JP
@EN
	@brief Start haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsStartHapticLoop(SPIDAR_HANDLE pAHS);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 力覚提示制御を有効・無効にする
	@param[in]	handle 対象となるSPIDARのハンドル
	@param[in]	isActive 力覚制御を有効にするとき1, 無効にするとき0
	@param[in]	spidar_id	設定対象となるSpidarのID<br>
							（省略可・省略時はすべてのSpidar_idが対象となる）<br>
							<b>SpidarGのとき</b>は1台分のみなので0を指定（省略推奨）<br>
							<b>Spidar4のとき</b>は2台分制御できるので0又は1を指定可能<br>
							<b>SpidarXのとき</b>は8本分の糸を制御できるので0から7を指定可能<br>
@END_JP
@EN
	@brief Start haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsActive         (SPIDAR_HANDLE pAHS,int isActive,   int spidar_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidarのキャリブレーションを行う
	@param[in]	handle 対象となるSPIDARのハンドル
	@param[in]	spidar_id	設定対象となるSpidarのID<br>
							（省略可・省略時はすべてのSpidar_idが対象となる）<br>
							<b>SpidarGのとき</b>は1台分のみなので0を指定（省略推奨）<br>
							<b>Spidar4のとき</b>は2台分制御できるので0又は1を指定可能<br>
							<b>SpidarXのとき</b>は8本分の糸を制御できるので0から7を指定可能<br>
@END_JP
@EN
	@brief Make calibration of Spidar
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsCalib          (SPIDAR_HANDLE pAHS,                int spidar_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 力覚提示制御ループの停止
	@param[in]	handle 対象となるSPIDARのハンドル
@END_JP
@EN
	@brief Stop haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsStopHapticLoop (SPIDAR_HANDLE pAHS);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spiarの終了処理<br>
	※注意：プログラムの終了時には必ず実行して正しくSpidarAPIを終了してください
	@param[in]	handle 対象となるSPIDARのハンドル
@END_JP
@EN
	@brief Quit Spidar
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API SPIDAR_HANDLE ahsQuit  (SPIDAR_HANDLE pAHS);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 並進速度の取得（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	posVel[3]	並進速度の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpPosVel   (SPIDAR_HANDLE pAHS,float posVel[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 回転速度の取得（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	posVel[3]	回転速度の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpOriVel   (SPIDAR_HANDLE pAHS,float posVel[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 並進位置の取得（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	pos[3]		並進位置の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpPos      (SPIDAR_HANDLE pAHS,float pos[3],   int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 回転姿勢の取得（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	ori[4]		クオータニオン(quaternion)による回転姿勢の値(w,x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpOri_wxyz (SPIDAR_HANDLE pAHS,float ori[4],   int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 並進提示力の設定（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	force[3]	並進提示力の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpForce    (SPIDAR_HANDLE pAHS,float force[3] ,int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 回転提示トルクの設定（インピーダンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	torque[3]	回転提示トルクの値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpTorque   (SPIDAR_HANDLE pAHS,float torque[3],int spidar_id = 0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 力覚ポインタのスケールの設定（インピーダンス制御用）
	@param[in]	handle			対象となるSPIDARのハンドル
	@param[in]	posGripScale	並進方向のスケール
	@param[in]	oriGripScale	回転方向のスケール
	@param[in]	spidar_id		設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpScale(SPIDAR_HANDLE pAHS,
								 float posGripScale,
								 float oriGripScale,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief VCのオブジェクト側の並進力と回転力のスケールの設定（インピーダンス制御用）
	@param[in]	handle			対象となるSPIDARのハンドル
	@param[in]	forceObjScale	並進力のスケール
	@param[in]	torqueObjScale	回転力のスケール
	@param[in]	spidar_id		設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsVcSetFTscale(SPIDAR_HANDLE pAHS,
								 float forceObjScale,
								 float torqueObjScale,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief バーチャルカップリングパラメータ設定（インピーダンス制御時）
	@param[in]	handle			対象となるSPIDARのハンドル
	
	@param[in]	posK			並進方向の剛性係数
	@param[in]	posB			並進方向の粘性係数

	@param[in]	oriK			回転方向の剛性係数
	@param[in]	oriB			回転方向の粘性係数
	
	@param[in]	spidar_id		設定対象となるSpidarのID
								（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/

SPIDARAHS_API void ahsVcSetKB(SPIDAR_HANDLE pAHS,
								 float posK,float posB,
								 float oriK,float oriB,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief バーチャルカップリングの更新（インピーダンス制御時）
	@param[in]	handle			対象となるSPIDARのハンドル
	@param[in]	isCoupling		カップリングを計算するかどうか 1ならば計算、0ならば計算しない

	@param[in]	posObj[3]		現在のオブジェクトの位置（x,y,zの順）
	@param[in]	posVelObj[3]	現在のオブジェクトの速度（x,y,zの順）
	@param[out]	forceObj[3]		カップリングにより得られた力（x,y,zの順）

	@param[in]	oriObj[4]		現在のオブジェクトの姿勢（クオーターニオン：w,x,y,zの順）
	@param[in]	oriVelObj[3]	現在のオブジェクトの姿勢の角速度（x,y,zの順）
	@param[out]	torqueObj[3]	カップリングにより得られたトルク（x,y,zの順）

	@param[in]	spidar_id		設定対象となるSpidarのID
								（省略可・省略時はすべてのSpidar_idが対象となる
								SpidarGのときは1台分のみなので0を指定（省略推奨），
								Spidar4のときは2台分制御できるので0又は1を指定可能，
								SpidarXのときは8本分の糸を制御できるので0から7を指定可能
								）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsVcUpdate(SPIDAR_HANDLE pAHS,
							   int isCoupling,	float simHz,
							   float posObj[3],float posVelObj[3],float forceObj[3], 
							   float oriObj[4]/*wxyz*/,float oriVelObj[3],float torqueObj[3],
							   int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 並進提示力の取得（アドミッタンス制御用）
	@brief Spidarの力覚提示部にかかる並進力を取得する
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	force[3]	並進提示力の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetAdmForce    (SPIDAR_HANDLE pAHS,float force[3], int spidar_id =  0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 回転提示トルクの取得（アドミッタンス制御用）
	@brief Spidarの力覚提示部にかかる回転トルクを取得する
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	torque[3]	回転提示トルクの値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・
							SpidarGのときは1台分のみなので0を指定，
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetAdmTorque   (SPIDAR_HANDLE pAHS,float torque[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 並進位置の設定（アドミッタンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	pos[3]		並進位置の値(x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetAdmPos      (SPIDAR_HANDLE pAHS,float pos[3],   int spidar_id = 0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 回転姿勢の設定（アドミッタンス制御用）
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[out]	ori[4]		クオータニオン(quaternion)による回転姿勢の値(w,x,y,zの順番)
	@param[in]	spidar_id	設定対象となるSpidarのID
							（省略可・省略時はすべてのSpidar_idが対象となる
							SpidarGのときは1台分のみなので0を指定（省略推奨），
							Spidar4のときは2台分制御できるので0又は1を指定可能，
							SpidarXのときは8本分の糸を制御できるので0から7を指定可能
							）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetAdmOri_wxyz (SPIDAR_HANDLE pAHS,float ori[4],   int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 外部スイッチ入力値の取得（デジタルスイッチ用）
	@brief 【未実装】
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	ch			スイッチのチャンネル番号
	@param[in]	spidar_id	設定対象となるSpidarのID（省略可・省略推奨）
	@return		対象スイッチの値
@END_JP
@EN
	@brief Get external switch value (for digital switch)
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API int   ahsGetDigitalSw  (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 外部スイッチ入力値の取得（アナログスイッチ用，タッチスイッチと内部でマルチプレクス）
	@brief 【未実装】
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	ch			スイッチのチャンネル番号
	@param[in]	spidar_id	設定対象となるSpidarのID（省略可・省略推奨）
	@return		対象スイッチの値
@END_JP
@EN
	@brief Get external switch value (for analog switch)
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API float ahsGetAnalogSw	 (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief タッチスイッチ入力値の取得（アナログスイッチと内部でマルチプレクス）
	@brief 【未実装】
	@param[in]	handle		対象となるSPIDARのハンドル
	@param[in]	ch			スイッチのチャンネル番号（最大:3ch）
	@param[in]	spidar_id	設定対象となるSpidarのID（省略可・省略推奨）
	@return		対象スイッチの値
@END_JP
@EN
	@brief Get Touch switch value
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API int ahsGetTouchSw	(SPIDAR_HANDLE pAHS,int ch,	int spidar_id = 0 );


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief 力覚提示制御ループの中で実行するユーザ関数（コールバック関数）の設定
	@brief　例）インピーダンス制御時におけるバーチャルカップリングの実装など
	@param[in]	handle	対象となるSPIDARのハンドル
	@param[in]	pf		制御ループ中で実行するコールバック関数<br>
						関数pf中で引数のdwUserを使って<br>
						SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;<br>
						とすることで、関数pf内で対応するSPIDAR_HANDLEが取得できます。<br>
						これによりハンドルhSpidarを使って対応するSpidarの位置情報・力情報などを取得・設定できます。
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetHapticLoopCallBackFunction(SPIDAR_HANDLE pAHS,  void (CALLBACK *pf)(DWORD dwUser));


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// 拡張機能

/**
@JP
	@brief 【拡張機能】値取得拡張機能のための種目定数<br>
			今後追加予定
@END_JP
@EN
@END_EN
*/
enum AhsGetEnum{
	GET_SPIDAR_NUM_IV1,				/**< @JP 本コントローラで制御できるSpidarの数を取得		(int型、ベクトル配列、サイズ：1) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_PHS_ALL8CH_CV8,			/**< @JP 8チャンネルすべてのエンコーダの相順の取得		(char型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_COUNT_ALL8CH_FV8,		/**< @JP 8チャンネルすべてのエンコーダカウント値の取得	(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_COUNT_ALL8x3CH_FV24,	/**< @JP 24(8x3)チャンネルすべてのエンコーダカウント値の取得	(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_WIRE_LENGTH_ALL8CH_FV8,		/**< @JP 8チャンネルすべてのワイヤの長さの取得			(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_MOTOR_POS0_ALL8CH_FV3x8,	/**< @JP 8チャンネルすべてのモータの位置の取得			(float型、ベクトル配列、サイズ：3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_MOTOR_POS0_ALL8x3CH_FV3x24,	/**< @JP 24(8x3)チャンネルすべてのモータの位置の取得	(float型、ベクトル配列、サイズ：3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_GRIP_POS0_ALL8CH_FV3x8,		/**< @JP 8チャンネルすべてのグリップ上のワイヤ接続位置（グリップがホームポジションの時）の取得 (float型、ベクトル配列、サイズ：3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_GRIP_POS0_ALL8x3CH_FV3x24,	/**< @JP 24(8x3)チャンネルすべてのグリップ上のワイヤ接続位置（グリップがホームポジションの時）の取得 (float型、ベクトル配列、サイズ：3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_PWM_DUTY_ALL8CH_FV8,
	GET_ADC_FORCE_ALL8CH_FV8,
	GET_ADC_RAW_ALL8CH_IV8,
	GET_ADC_FIR_RAW_ALL8CH_IV8,


	GET_PID_TARGET_ALL8CH_IV8,		/**< @JP 8チャンネルすべてのPID目標値の値を取得			(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_PID_AMP_TEST_ALL8CH_FV8,	/**< @JP PIDテスト用									(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	
	GET_ADM_PID_PV_TEST_ALL8CH_IV8,		/**< @JP PIDテスト用 PIDの制御量（計測値）				(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PIDテスト用 PIDの目標値						(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのP比例係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのI積分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのD微分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/

	GET_IMP_PID_PV_TEST_ALL8CH_IV8,		/**< @JP PIDテスト用 PIDの制御量（計測値）				(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PIDテスト用 PIDの目標値						(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのP比例係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのI積分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのD微分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/

	GET_VC_POS_ORI_NORM_FV2,			/**< @JP VCの位置姿勢のノルム(float型、ベクトル配列、サイズ：2) @END_JP @EN Get all encoder count. @END_EN*/

	GET_HAPTIC_LOOP_MSEC_IV1,		/**< @JP ハプティックループの更新周期の取得[msec]			(int型、ベクトル配列、サイズ：1) @END_JP @EN Get all motor position. @END_EN*/

	GET_SH_SEND_DATA_LEN_UCV1,
	GET_SH_RECEIVE_DATA_LEN_UCV1,

	GET_API_VER_STR_CV128,
	GET_API_COPY_RIGHT_STR_CV128,
	AHS_GET_ENUM_MAX				/**< @JP 列挙型のサイズ取得のためのダミー @END_JP @EN Dummy. @END_EN*/
};

/**
@JP
	@brief 【拡張機能】値設定拡張機能のための種目定数<br>
			今後追加予定
@END_JP
@EN
@END_EN
*/
enum AhsSetEnum{

	SET_PWM_DUTY_PERCENT_ALL8CH_FV8,
	SET_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PIDテスト用 PIDの目標値						(int型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのP比例係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのI積分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PIDテスト用 PIDのD微分係数						(float型、ベクトル配列、サイズ：8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_MODE_IV8,

	SET_SH_HAPTIC_RENDERING_TYPE_CV1,
	AHS_SET_ENUM_MAX			/**< @JP 列挙型のサイズ取得のためのダミー @END_JP @EN Dummy. @END_EN*/
};


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>【拡張機能】</b>値の取得関数
	@param[in]	pAHS			対象となるSPIDARのハンドル
	@param[in]	AhsGetEnum		取得したい値の種目定数　種目定数の最後の部分によりデータ型、データ幅などが決定されている<br>
								例）エンコーダの値を8チャンネル分取得する<br>
								GET_ENC_COUNT_ALL8CH_IV8<br>
								I:int型のデータ<br>
								V:ベクトル配列<br>
								8:8データ分<br>
								を意味する。
	@param[out]	param			取得する値（ポインタ）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetVal(SPIDAR_HANDLE pAHS,AhsGetEnum cap,void* param);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>【拡張機能】</b>値の設定関数
	@param[in]	pAHS			対象となるSPIDARのハンドル
	@param[in]	AhsGetEnum		設定したい値の種目定数　種目定数の最後の部分によりデータ型、データ幅などが決定されている<br>
								例）エンコーダの値を8チャンネル分取得する<br>
								GET_ENC_COUNT_ALL8CH_IV8<br>
								I:int型のデータ<br>
								V:ベクトル配列<br>
								8:8データ分<br>
								を意味する。
	@param[in]	param			設定する値（ポインタ）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetVal(SPIDAR_HANDLE pAHS,AhsSetEnum cap,void* param);





//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>【SH 拡張機能】SHが接続されていないシステムでは無効，</b>SH1への値の設定と取得関数
	@param[in]	pAHS			対象となるSPIDARのハンドル
	@param[in]	w_size			SH1に設定するデータのサイズ(Byte)
	@param[in]	w_address		SH1に設定するデータのアドレス（SH1のアドレス）
	@param[in]	w_data			SH1に設定するデータ
	@param[in]	r_address		SH1から取得するデータのアドレス
	@param[out]	r_data			SH1から取得したデータ
	@return		SH1から取得したr_address番地のデータr_dataが有効かどうか（0無効：1有効）
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API int ahsSh1SetGetVal(SPIDAR_HANDLE pAHS,unsigned char w_size,unsigned long w_address,unsigned char w_data[48],unsigned long r_address,unsigned char r_data[52],unsigned char id = 0x0c);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>【SH 拡張機能】SHが接続されていないシステムでは無効
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API unsigned long ahsSh1GetAddress(SPIDAR_HANDLE pAHS,int id);
