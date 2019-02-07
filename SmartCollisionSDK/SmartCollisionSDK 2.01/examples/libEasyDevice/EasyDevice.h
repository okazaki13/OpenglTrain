#ifndef _EASYDEVICE_H_
#define _EASYDEVICE_H_

/** @file
 *  @brief This file is Definition of Class EasyDevice.
 *
 *	@author		3D Incorporated
 *	@date		2005/11/10
 *
 */

#define EH_LEFT_BUTTON   1
#define EH_RIGHT_BUTTON  2
#define EH_MIDDLE_BUTTON 3
#define EH_DOWN 11
#define EH_UP   12

#define EH_BUTTON_DOWN   1
#define EH_BUTTON_UP     2
#define EH_BUTTON_ON     3
#define EH_BUTTON_OFF    0

#define KEY_STATUS_NONE 0
#define KEY_STATUS_DOWN 1
#define KEY_STATUS_UP   2

/** @brief A Easy way to use Input/Output device in SmartCollision Application.
 *
 *  This class provides a easy way to control Human I(/O) Devices by
 *	hiding Device dependent routine.
 *
 *  - This class is a group of interface method for SmartCollision Application.
 *
 *  @note This is supporting PHANTOM or MOUSE only. 
 */
class CoordinateMatrix;
class EasyDevice{
private:
	double hapticFrequency;
	double collisionFrequency;
	void*collisionUserData;
	void*hapticsUserData;
        int runFlag;
protected:
	CoordinateMatrix*matrix;
	void(*callBackClFunction)(void*);
	void EnterCollisionThread(void);
	void LeaveCollisionThread(void);
	void EnterHapticThread(void);
	void LeaveHapticThread(void);
public:
	/** @brief Constructor
	 *
	 *  @param void
	 */
    EasyDevice(void);

	/** @brief Destructor
	 *
	 *  @param void
	 */
    ~EasyDevice(void);

	/** @name Initialize. */
	/// \{
	/** @brief Initialize.
	 *
	 *  @param void
	 *
	 */
    void Initialize(void);

	/** @name Start & Stop scheduler thread. */
	/// \{
	/** @brief Initialize and Start scheduler thread.
	 *
	 *  @param void
	 *
	 */
    bool Start(void);

	/** @brief Stop scheduler thread.
	 *
	 *  @param void
	 *
	 */
    bool Stop(void);
	/// \}

	/** @name Set & Get values from device.*/
	/// \{
	/** @brief Set Force to device.
	 *
	 *  @param const float force[3]
	 *
	 */
	void SetForce(const float force[3]);

	/** @brief Set Force to device.
	 *
	 *  @param const double force[3]
	 *
	 */
	void SetForce(const double force[3]);

	/** @brief Set Torque to device.
	 *
	 *  @param const float torque[3]
	 *
	 */
	void SetTorque(const float torque[3]);

	/** @brief Set Torque to device.
	 *
	 *  @param const double torque[3]
	 *
	 */
	void SetTorque(const double torque[3]);

	/** @brief Set Scale to class.
	 *
	 *  @param float scale
	 *
	 */
	void SetScale(float scale);

	/** @brief Set Scale to class.
	 *
	 *  @param double scale
	 *
	 */
	void SetScale(double scale);

	/** @brief Set Orientation to class.
	 *
	 *  @param const float orientation[4]
	 *
	 */
	void SetOrientation(const float orientation[4]);

	/** @brief Set Orientation to class.
	 *
	 *  @param const double orientation[4]
	 *
	 */
	void SetOrientation(const double orientation[4]);

	/** @brief Reset Orientation to class.
	 *
	 *  @param 
	 *
	 */
	void ResetOrientation(void);

	/** @brief Get Position from device.
	 *
	 *  @param float position[3]
	 *
	 */
	void GetPosition(float position[3]);

	/** @brief Get Position from device.
	 *
	 *  @param double position[3]
	 *
	 */
	void GetPosition(double position[3]);

	/** @brief Get Orientation from device.
	 *
	 *  @param float orientation[4]
	 *
	 */
	void GetOrientation(float orientation[4]);

	/** @brief Get Orientation from device.
	 *
	 *  @param double orientation[4]
	 *
	 */
	void GetOrientation(double orientation[4]);

    /** @brief Get last matrix from class.
	 *
	 *  @param float matrix[16]
	 *
	 */
	void GetLastMatrix(float matrix[16]);

	/** @brief Get last matrix from class.
	 *
	 *  @param double matrix[16]
	 *
	 */
	void GetLastMatrix(double matrix[16]);
	/** @brief Get last raw matrix from class.
	 *
	 *  @param float matrix[16]
	 *
	 */
	void GetLastRawMatrix(float matrix[16]);

	/** @brief Get last raw matrix from class.
	 *
	 *  @param double matrix[16]
	 *
	 */
	void GetLastRawMatrix(double matrix[16]);

	/** @name Set Callback function.*/
	/// \{
	/** @brief Set Haptic CALLBACK function pointer to class.
	 *
	 *  @param void(*hpfunction)(void)
	 *
	 *  @note  To call haptic loop without using this method 
	 *			must be not thread safe.
	 */
	void SetHapticFunction(  void(*hpfunction)(void*),void*userData,double frequency=1000);

	/** @brief Set Collision CALLBACK function pointer to class.
	 *
	 *  @param void(*clfunction)(void)
	 *
	 *  @note  To call collision loop without using this method 
	 *			must be not thread safe.
	 */
	void SetCollisionFunction(  void(*clfunction)(void*),void*userData,double frequency=1000);

	/** @brief Set Collision status CALLBACK function pointer to class.
	 *
	 *  @param void(*function)(void)
	 *
	 *  @note  To call collision status function without using this method 
	 *			must be not thread safe.
	 */
	void SetCollisionStatusFunction(  void(*function)(void*),void*userData=0); 

	/** @brief Set Haptic status CALLBACK function pointer to class.
	 *
	 *  @param void(*function)(void)
	 *
	 *  @note  To call haptic status function without using this method 
	 *			must be not thread safe.
	 */
	void SetHapticStatusFunction(  void(*function)(void*),void*userData=0); 

	/** @brief Set Keyboard status CALLBACK function pointer to class.
	 *
	 *  @param void(*kbfunction)(unsigned char)
	 *	@param unsigned char key
	 *
	 *  @note  To call keyboard function without using this method 
	 *			must be not thread safe.
	 */
	void SetKeyboardFunction(void(*kbfunction)(unsigned char,int,void*),
                             unsigned char key,int status,void*userData=0); 
	/// \}

	/** @name Mouse function.*/
	/// \{
	/** @brief Mouse button manipulate function.
	 *
	 *  @param int button
	 *  @param int state
	 *  @param int x
	 *  @param int y
	 *
	 *  @note  For mouse only.
	 */
	void MouseFunction(int button,int state, int x, int y);

	/** @brief Mouse motion manipulate function.
	 *
	 *  @param int x
	 *  @param int y
	 *
	 *  @note  For mouse only.
	 */
	void MotionFunction(int x, int y);

	/** @brief Window reshape function.
	 *
	 *  @param int w
	 *  @param int h
	 *
	 *  @note  For mouse only.
	 */
	void ReshapeFunction(int w,int h);
	/// \}

	/** @brief Get Button from device.
	 *
	 *  @param	int n
	 *
	 *	@note	Call this from CALLBACK function. 
	 */
	int  GetButton(int n);
	/// \}

	/** @brief Collision function.
	 *
	 *  @param	
	 *
	 *	@note	Call this from CALLBACK function. 
	 */
	void CallBackClFunction(void);
	/// \}

	/** @name Misc function.*/
	/// \{
	/** @brief Wait for user admition
	 *
	 *  @param 
	 *
	 *  @note  This is wait for user preparedness to start.
	 */
	void WaitForUserAdmit();
	/// \}

	/** @brief Set matrix
	 *
	 *  @param double m[16]
	 *
	 *  @note  This function sets matrix
	 */
	void SetMatrix(const double m[16]);
	/// \}

	/** @brief Set matrix
	 *
	 *  @param float m[16]
	 *
	 *  @note  This function sets matrix
	 */
	void SetMatrix(const float m[16]);
	/// \}

	/** @brief Get matrix
	 *
	 *  @param double m[16]
	 *
	 *  @note  This function gets matrix
	 */
	void GetMatrix(double m[16])const;
	/// \}

	/** @brief Get matrix
	 *
	 *  @param float m[16]
	 *
	 *  @note  This function gets matrix
	 */
	void GetMatrix(float m[16])const;
	/// \}
	class Impl;
	Impl* impl_;
};
#endif
