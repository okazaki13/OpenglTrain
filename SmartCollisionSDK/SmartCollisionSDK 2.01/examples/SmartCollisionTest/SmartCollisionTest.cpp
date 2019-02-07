/** @file
 *  @brief		SmartCollision Test application.
 *
 *	@author		3D Incorporated
 *	@date		2006/08/03
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "EasyDevice.h"
#include "sc.h"
#ifdef USE_SPO
#include "spo.h"
#endif

#include"MathUtility.h"

// Constructor of EasyDevice
EasyDevice device;

// Definition of SCSceneManager mode
//#define SC_MODE SC_SCENE_MANAGER_TRIANGLE_SOUP
#define SC_MODE SC_SCENE_MANAGER_CLOSED_POLYHEDRA

// Constructor of SCSceneManager
SCSceneManager manager(SC_MODE);

// Parameter of SCSceneManager
static double tolerance=1e-3;	  // Tolerance of penetration depth
static double maxDistance=1;	  // Maximum value of minimum disance calculation
static double forceStiffness=0.4; //Coefficient of spring stiffness[N/(mm)]
static double torqueStiffness=150;//Coefficient of spring torque stiffness[NEm]
static int maxIteration=10;       //Maximum iteration number for collision calculation
static int rotationMode=3;				 // Current Rotation mode

// Status
double pointerPosition[3]; 		 // Position of haptic pointer
double pointerOrientation[4];	 // Orientation of haptic pointer
double pointerMatrix[16];		 // Matrix of haptic pointer
int connectFlag=0;				 // Status Flag for object and haptic pointer
int forceFlag=1;				 // Flag for outputting force and torque
int displayContactObjectFlag=1;	 // Flag for displaying contact object
//
double lastPointerPosition[3];	 // Last position of haptic pointer
double lastPointerOrientation[4];// Last orientation of haptic pointer
double lastContactPosition[3];   // Last contact position
double lastContactOrientation[4];// Last contact orientation
double lastDistance;
int lastResult=SC_ERROR_NO_RESULT;
int buttonCount;
int setOrientationFlag;
int disableForceFlag=1;
// Result of Collision calculation
int result=SC_NO_ERROR;			// Result value of Collision calculation
double distance;				// Minumum distance(>0) or penetration depth(<=0)
double distance0=-1;			// Minumum distance or penetration depth of previous frame
int targetObjectID;             // ID of target   object
int opponentObjectID;           // ID of opponent object
double point1[3];				// A tip of target of manupurating
double point2[3];				// A tip of still object
double contactPosition[3];      // Contact position of controlled object
double contactOrientation[4];   // Contact orientation of controlled object
double ipdm[16];				// Inverse Penetration matrix
int latestResult=SC_ERROR_NO_RESULT;   // Latest result value of Collision calculation
double latestDistance;			// Latest distance

// Window size
static int wx=1024,wy=768;		// Default Window size
static double scale=1;			// Scale of haptic pointer Position

//Valuable for graphics
double projection[16]={
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1};					// Projection matrix
double modelview[16]={
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1};					// Model view matrix

// Definition of object class
struct Object
{
    int id;						// Object ID for SCSceneManager
    SCObject* object;			// SmartColllision Object
    int controlledFlag;			// Flag for handling object
    // Information for drawing
    double* vertex;				// Vertex array
    int vertexSize;				// Number of vertex
    int* face;					// Index array
    int faceSize;				// Number of triangle
    double* normal;				// Normal vector
    double matrix[16];			// Matrix
};

#define OBJECT_MAX 100
int objectSize=0;
Object object[OBJECT_MAX];
Object hapticPointerObject;

/** @brief	Index of object
 *
 *	@param	int id
 *
 *	@note
 */
int GetObjectIndex(int id)
{
    int i;
    for(i=0;i<objectSize;i++)
      {
          if(object[i].id==id)
            return i;
      }
    return -1;
}

/** @brief	Normalize of vector
 *
 *	@param	double* a
 *
 *	@note
 */
void Normalize3(double* a)
{
    double t;
    t=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    if(t==0)t=1;
    t=1.0/t;
    a[0]*=t;
    a[1]*=t;
    a[2]*=t;
}

/** @brief	Get Normal vector
 *
 *	@param	double n[3]
 *	@param	double v1[3]
 *	@param	double v2[3]
 *	@param	double v3[3]
 *
 *	@note
 */
void GetNormal(double n[3],double v1[3],double v2[3],double v3[3])
{
    double a[3],b[3];
    a[0]=v2[0]-v1[0];
    a[1]=v2[1]-v1[1];
    a[2]=v2[2]-v1[2];
    b[0]=v3[0]-v1[0];
    b[1]=v3[1]-v1[1];
    b[2]=v3[2]-v1[2];
    n[0]=a[1]*b[2]-a[2]*b[1];
    n[1]=a[2]*b[0]-a[0]*b[2];
    n[2]=a[0]*b[1]-a[1]*b[0];
    Normalize3(n);
}

/** @brief	PrintUsage
 *
 *	@param
 *
 *	@note
 */
void PrintUsage()
{
    printf("Usage: SmartCollisionTest [glut options] file...\n");
    printf(" ' ': Connect the controlled object by its origin.\n");
    printf(" 'f': Toggle force and torque feedback.\n");
    printf(" 'r': Change rotation mode.\n");
    printf(" 'q': Quit.\n");
    printf(" 'h': Print this message.\n");
    printf(" Touch object: Toggle controlled/static object.\n");
}

/** @brief	Drawing Object
 *
 *	@param	Object*	o
 *	@param	float*	diffuse
 *	@param	double	scale=1
 *
 *	@note
 */
void DrawObject(Object* o, float* diffuse)
{
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_BACK,GL_DIFFUSE,diffuse);

    glBegin(GL_TRIANGLES);
    for(int i=0;i<o->faceSize;i++)
      {
          int n1,n2,n3;
          n1=o->face[3*i+0];
          n2=o->face[3*i+1];
          n3=o->face[3*i+2];
          glNormal3f(o->normal[3*i+0],o->normal[3*i+1],o->normal[3*i+2]);
          glVertex3f(o->vertex[3*n1+0],
                     o->vertex[3*n1+1],
                     o->vertex[3*n1+2]);
          glNormal3f(o->normal[3*i+0],o->normal[3*i+1],o->normal[3*i+2]);
          glVertex3f(o->vertex[3*n2+0],
                     o->vertex[3*n2+1],
                     o->vertex[3*n2+2]);
          glNormal3f(o->normal[3*i+0],o->normal[3*i+1],o->normal[3*i+2]);
          glVertex3f(o->vertex[3*n3+0],
                     o->vertex[3*n3+1],
                     o->vertex[3*n3+2]);
      }
    glEnd();
}

/** @brief	Get Status from the SCSceneManager
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void GetCollisionStatus(void*pData)
{
    // Get latest result
    latestResult=result;
    // Get latest distance
    latestDistance=distance;
    // Get latest pointer matrix
    device.GetLastRawMatrix(pointerMatrix);
    manager.GetStatus(SC_POINT_ON_CONTROLLED_OBJECT,point1);
    manager.GetStatus(SC_POINT_ON_STATIC_OBJECT,point2);
    // Inverse penetration matrix
    manager.GetStatus(SC_PD_INVERSE_MATRIX,ipdm);
    for(int i=0;i<objectSize;i++)
      {
          if(object[i].controlledFlag)
            {
                // Get matrix of operating object
                object[i].object->GetTransformation(SC_TRANSFORMATION_MATRIX,
                                                    object[i].matrix);
            }
      }
    return;
}

/** @brief	Set a source of diffuse light to position of haptic pointer
 *
 *	@param
 *
 *	@note
 */
void MakePointerLight()
{
    if(connectFlag==0)
      {
          float t[4];
          t[0]=pointerPosition[0];
          t[1]=pointerPosition[1];
          t[2]=pointerPosition[2];
          t[3]=1;
          glEnable(GL_LIGHT1);
          glLightfv(GL_LIGHT1,GL_POSITION,t);
          t[0]=1;
          t[1]=0.8;
          t[2]=0.3;
          glLightfv(GL_LIGHT1,GL_DIFFUSE,t);
          t[0]=1e0;
          glLightfv(GL_LIGHT1,GL_CONSTANT_ATTENUATION,t);
      }
    else
      glDisable(GL_LIGHT1);
    return;
}

/** @brief	Show the Result of collision calculation
 *
 *	@param
 *
 *	@note
 */
void ShowCollisionStatus()
{
    if(result==SC_NO_ERROR)
      {
          if(latestDistance>0)
            {// Draw a line in between nearest tips
                glDisable(GL_LIGHTING);
                glColor3f(1,1,1);
                glBegin(GL_LINES);
                glVertex3d(point1[0],point1[1],point1[2]);
                glVertex3d(point2[0],point2[1],point2[2]);
                glEnd();
                glEnable(GL_LIGHTING);
            }
          else
            {// Set a source of ambient light to contact position
                float t[4];
                t[0]=point1[0];
                t[1]=point1[1];
                t[2]=point1[2];
                t[3]=1;
                glEnable(GL_LIGHT2);
                glLightfv(GL_LIGHT2,GL_POSITION,t);
                t[0]=1;
                t[1]=0.0;
                t[2]=0.0;
                glLightfv(GL_LIGHT2,GL_AMBIENT,t);
                t[0]=0;
                glLightfv(GL_LIGHT2,GL_CONSTANT_ATTENUATION,t);
                t[0]=1e-2/(scale*scale);
                glLightfv(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,t);
            }
      }
    return;
}

/** @brief	Draw the haptic pointer
 *
 *	@param
 *
 *	@note
 */
void DrawHapticPointer()
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
    float c[4];
    {
        c[0]=0.8;
        c[1]=0.4;
        c[2]=0;
        c[3]=1;
        glPushMatrix();
        glMultMatrixd(pointerMatrix);
        DrawObject(&hapticPointerObject,c);
        glPopMatrix();
    }
    return;
}

/** @brief	Draw whole the scene including haptic pointer
 *
 *	@param
 *
 *	@note
 */
void DrawScene()
{
    // Get the Result of collision calculation
    device.SetCollisionStatusFunction(GetCollisionStatus);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    MakePointerLight();
    ShowCollisionStatus();
    DrawHapticPointer();

    float c[4];
    c[3]=1;
    for(int i=0;i<objectSize;i++)
      {// configuration of material
          if(object[i].controlledFlag)
            {
                if(connectFlag!=1)
                  {
                      c[0]=0;
                      c[1]=0.8;
                      c[2]=0.8;//light blue
                  }
                else
                  {// change the light color by condition of collision
                      switch(latestResult)
                        {
                          case SC_NO_ERROR:
                            if(latestDistance>0)
                              {// Not in collision
                                  c[0]=0;
                                  c[1]=0.8;
                                  c[2]=0;//green
                              }
                            else
                              {// In Collision
                                  if(displayContactObjectFlag)
                                    {
                                        c[0]=0.8;
                                        c[1]=0.8;
                                        c[2]=0.0;//yellow
                                    }
                                  else
                                    {
                                        c[0]=0.8;
                                        c[1]=0.0;
                                        c[2]=0.0;//red
                                    }
                              }
                            break;
                          case SC_ERROR_INVALID_INITIAL_TRANSFORMATION:
                            c[0]=0.8;
                            c[1]=0;
                            c[2]=0.8;
                            break;// purple
                          case SC_ERROR_UNKNOWN_DISTANCE:
                            c[0]=0.0;
                            c[1]=0.4;
                            c[2]=0.0;
                            break;// dark green
                          case SC_ERROR_FAILED:
                            c[0]=0.0;
                            c[1]=0.0;
                            c[2]=0.8;
                            break;// blue
                          default:
                            c[0]=c[1]=c[2]=0.3;
                            break;// grey
                        }
                  }
            }
          else
            {
                c[0]=c[1]=c[2]=0.5;
            }
          // Draw objects
          glPushMatrix();

          if(displayContactObjectFlag&&
             connectFlag==1&&
             object[i].controlledFlag&&
             latestResult==SC_NO_ERROR&&
             distance<=0)
            {
                glMultMatrixd(ipdm);// Inverse matrix
            }
          glMultMatrixd(object[i].matrix);
          DrawObject(object+i,c);
          glPopMatrix();
      }
}

/** @brief	Display function
 *
 *	@param
 *
 *	@note	This is mainly called from idle function
 */
void Display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixd(projection);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixd(modelview);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    DrawScene();
    glFlush();
    glutSwapBuffers();
}

/** @brief	Add/Remove a target object
 *
 *	@param	bool flag
 *
 *	@note
 */
bool ConnectObject(bool flag)
{
    int i,j=0;
    if(flag)
      {// Disable the pointer object
          manager.DeleteControlledObject(hapticPointerObject.id);
          manager.DeactivateObject(hapticPointerObject.id);
      }
    else
      {
          if(result==SC_NO_ERROR&&distance<=0&&displayContactObjectFlag)
            {
                // Sets contact transformation,if the contact object is displayed
                manager.SetTransformation(SC_POSITION_WORLD_CENTER,contactPosition);
                manager.SetTransformation(SC_ORIENTATION_QUATERNION,contactOrientation);
            }
      }
    for(i=0;i<objectSize;i++)
      {// Add/Remove a target object
          if(object[i].controlledFlag)
            {
                if(flag)
                  {
                      manager.AddControlledObject(object[i].id);
                      j++;
                  }
                else
                  {
                      manager.DeleteControlledObject(object[i].id);
                  }
            }
      }
    if(j==0||!flag)
      {// Enable the pointer object
          manager.ActivateObject(hapticPointerObject.id);
          manager.AddControlledObject(hapticPointerObject.id);
          distance0=-1;
      }
    disableForceFlag=1;
    return j>0; // Target object exists or not
}

void GetExtrapolatedPenetrationDepth(double tpdv[3],double rpdv[3],
                                     const double cp[3],const double cq[4],
                                     const double p [3],const double q [4])
{
    tpdv[0]=p[0]-cp[0];
    tpdv[1]=p[1]-cp[1];
    tpdv[2]=p[2]-cp[2];
    double t[4],rpdq[4];
    CopyVector(t,cq,4);
    InvertQuaternion(t);
    MultiplyQuaternion(rpdq,q,t);
    FromQuaternionToVector(rpdv,rpdq);
}

/** @brief	Get haptic status
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void GetHapticStatus(void*pData)
{
    if(buttonCount>0)
      {
          if(!connectFlag)
            {
                if(ConnectObject(true))
                  {
                      manager.SetTransformation(SC_POSITION_NEW_WORLD_CENTER,
                                                pointerPosition);
                      double q[4];
                      manager.GetTransformation(SC_ORIENTATION_QUATERNION,q);
                      //device.SetOrientation(q);
                      CopyVector(pointerOrientation,q,4);
                      connectFlag=1;
                      setOrientationFlag=1;
                  }
            }
          else
            {
                ConnectObject(false);
                connectFlag=0;
            }
        buttonCount--;
      }
    CopyVector(lastPointerPosition,pointerPosition,3);
    CopyVector(lastPointerOrientation,pointerOrientation,4);
}

/** @brief	Set haptic status
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void SetHapticStatus(void*pData)
{
    CopyVector(lastContactPosition,contactPosition,3);
    CopyVector(lastContactOrientation,contactOrientation,4);
    lastDistance=distance;
    lastResult=result;
}

/** @brief	Collision Loop
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void CollisionFunction(void*pData)
{
    // (1) Get Haptic status
    device.SetHapticStatusFunction(GetHapticStatus,0);
    // (2) Set Haptic pointer Status to the SCSceneManager
    manager.SetTransformation(SC_POSITION_WORLD_CENTER,lastPointerPosition);
    manager.SetTransformation(SC_ORIENTATION_QUATERNION,lastPointerOrientation);

    // (3) Renew an attribute of SCSceneManager
    switch(rotationMode)
      {// Configuration of rotation mode
        case 0:
          manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,
                                   SC_ROTATION_MODE_NONE );
          break;
        case 1:
          manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,
                                   SC_ROTATION_MODE_FREE );
          break;
        case 2:
          manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,
                                   SC_ROTATION_MODE_INPUT);
          break;
        case 3:
          manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,
                                   SC_ROTATION_MODE_MIX  );
          break;
      }

    // (4) Update status of collision calculation
    result=manager.UpdateStatus();

    // (5) Get the Result of collision calculation
    if(result==SC_NO_ERROR)
      {
          // Get the penetration depth or distance in between object
          manager.GetStatus(SC_DISTANCE, &distance);
          if(distance<=0.0)
            {// There is intersection
                //manager.GetStatus(SC_TPD_VECTOR,tpdv);
                //manager.GetStatus(SC_RPD_VECTOR,rpdv);
                manager.GetStatus(SC_CONTACT_POSITION,contactPosition);
                manager.GetStatus(SC_CONTACT_ORIENTATION,contactOrientation);
            }
          else
            {
                disableForceFlag=0;
            }
          // Get the ID of opponent object
          //manager.GetStatus(SC_OPPONENT_OBJECT_ID,&opponentObjectID);
          int oids[2];
          manager.GetStatus(SC_OBJECT_ID,oids);
          targetObjectID=oids[0];
          opponentObjectID=oids[1];
          if(connectFlag==0)
            {// In case of touching still object, controlledFlag will be toggled
                if(opponentObjectID>=0&&distance0>0&&distance<=0)
                  {
                      int i=GetObjectIndex(opponentObjectID);
                      object[i].controlledFlag^=1;
                  }
            }
          //manager.GetStatus(SC_OBJECT_ID,oids);
          distance0=distance;// Set the distance(or PD) of previous frame
      }
    else if(result==SC_ERROR_UNKNOWN_DISTANCE)
      {
          disableForceFlag=0;
      }

    device.SetHapticStatusFunction(SetHapticStatus,0);
}
/** @brief	Haptics Loop
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void HapticFunction(void*pData)
{
    if(setOrientationFlag){
        device.SetOrientation(pointerOrientation);
        setOrientationFlag=0;
    }
    // (1) Get direction and position of Haptic pointer
    device.GetPosition(pointerPosition);
    device.GetOrientation(pointerOrientation);

    if(device.GetButton(0)==EH_BUTTON_DOWN)
      {
          buttonCount++;
      }
    // (2) Configuration of force and torque
    double force[3]={0,0,0}; 
    double torque[3]={0,0,0};
    if(disableForceFlag==0&&
       lastResult==SC_NO_ERROR&&
       lastDistance<=0&&
       forceFlag){
        double tpdv[3],rpdv[3];
        GetExtrapolatedPenetrationDepth(tpdv,rpdv,
                                        lastContactPosition,lastContactOrientation,
                                        pointerPosition,pointerOrientation);
          force [0]=tpdv[0]*(-forceStiffness/scale);
          force [1]=tpdv[1]*(-forceStiffness/scale);
          force [2]=tpdv[2]*(-forceStiffness/scale);
          torque[0]=rpdv[0]*(-torqueStiffness);
          torque[1]=rpdv[1]*(-torqueStiffness);
          torque[2]=rpdv[2]*(-torqueStiffness);
    }
    device.SetForce(force);
    device.SetTorque(torque);
}

/** @brief	Idle function
 *
 *	@param
 *
 *	@note	This is called from GLUT
 */
void Idle()
{
    Display();
}

/** @brief	Mouse function
 *
 *	@param	int button
 *	@param	int state
 *	@param	int x
 *	@param	int y
 *
 *	@note	This is called from GLUT
 */
void Mouse(int button, int state, int x, int y)
{
    if(button==GLUT_RIGHT_BUTTON){
        if(state==GLUT_DOWN)
          device.MouseFunction(EH_RIGHT_BUTTON,EH_DOWN,x,y);
        else if(state==GLUT_UP)
          device.MouseFunction(EH_RIGHT_BUTTON,EH_UP,x,y);
    }else if(button==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN)
          device.MouseFunction(EH_LEFT_BUTTON,EH_DOWN,x,y);
        else if(state==GLUT_UP)
          device.MouseFunction(EH_LEFT_BUTTON,EH_UP,x,y);
    }else if(button==GLUT_MIDDLE_BUTTON){
        if(state==GLUT_DOWN)
          device.MouseFunction(EH_MIDDLE_BUTTON,EH_DOWN,x,y);
        else if(state==GLUT_UP)
          device.MouseFunction(EH_MIDDLE_BUTTON,EH_UP,x,y);
    }
}

/** @brief	Keyboard function
 *
 *	@param	unsigned char key
 *
 *	@note	This should be called as CALLBACK
 */
void KeyOperate(unsigned char key,int status,void*pData)
{
    switch(key)
      {
        case 'C':
          displayContactObjectFlag^=1;
          break;
        case ' ':
          buttonCount++;
          break;
        case 'f':
          forceFlag^=1;
          printf("Force: %s\n",forceFlag?"on":"off");
          break;
        case 'r':
          {// Change rotation mode
              rotationMode++;
              if(rotationMode>3)
                rotationMode=0;
              const char* s="";
              switch(rotationMode)
                {
                  case 0:
                    s="None";
                    break;
                  case 1:
                    s="Free";
                    break;
                  case 2:
                    s="Input";
                    break;
                  case 3:
                    s="Mix";
                    break;
                }
              printf("Rotation mode: %s\n",s);
              break;
          }
        case 'h':
          PrintUsage();
          break;
        case 'q':
          exit(0);
          break;
      }
    return;
}

/** @brief	KeyBoard function
 *
 *	@param	unsigned char key
 *	@param	int x
 *	@param	int y
 *
 *	@note	This is called from GLUT
 */
void Key(unsigned char key, int x, int y)
{
    device.SetKeyboardFunction( KeyOperate, key,0,0);
}

/** @brief	Mouse motion function
 *
 *	@param	int x
 *	@param	int y
 *
 *	@note	This is called from GLUT
 */
void Motion(int x, int y)
{
    device.MotionFunction(x,y);
}

/** @brief	Window reshape function
 *
 *	@param	int w
 *	@param	int h
 *
 *	@note	This is called from GLUT
 */
void Reshape(int w, int h)
{
    device.ReshapeFunction(w,h);
    projection[5]=projection[0]*(double)w/(double)h;
    wx=w;
    wy=h;
    glViewport(0, 0, w, h);
}

/** @brief	Load an object from file
 *
 *	@param	Object*		o
 *	@param	const char* file
 *
 *	@note
 */
bool LoadObject(Object* o, const char* file)
{
    printf("Loading object '%s'...\n",file);
    FILE*fp;
    fp=fopen(file,"r");
    if(fp==NULL)
      return false;
    o->vertexSize=0;
    o->faceSize=0;
    // Count the number of vertex and the number of faces
    for(;;)
      {
          char s[2000];
          int c;
          c=getc(fp);
          if(c==EOF)
            break;
          ungetc(c,fp);
          fgets(s,2000,fp);
          double v[3];
          int f[3];
          if(sscanf(s,"v %lg %lg %lg",v+0,v+1,v+2)==3)
            o->vertexSize++;
          if(sscanf(s,"f %d %d %d",f+0,f+1,f+2)==3)
            o->faceSize++;
      }
    rewind(fp);
    o->vertex=new double[o->vertexSize*3];
    o->face=new int[o->faceSize*3];
    int i=0,j=0;
    // Put vertices and faces to array
    for(;;)
      {
          char s[2000];
          int c;
          c=getc(fp);
          if(c==EOF)
            break;
          ungetc(c,fp);
          fgets(s,2000,fp);
          if(sscanf(s,"v %lg %lg %lg",
                    o->vertex+3*i+0,
                    o->vertex+3*i+1,
                    o->vertex+3*i+2)==3)
            {
                i++;
            }
          int f[3];
          if(sscanf(s,"f %d %d %d",f+0,f+1,f+2)==3)
            {
                o->face[3*j+0]=f[0]-1;
                o->face[3*j+1]=f[1]-1;
                o->face[3*j+2]=f[2]-1;
                j++;
            }
      }
    fclose(fp);
    // Calculation of normal vector
    o->normal=new double[o->faceSize*3];
    for(i=0;i<o->faceSize;i++)
      {
          GetNormal(o->normal+3*i,
                    o->vertex+3*o->face[3*i+0],
                    o->vertex+3*o->face[3*i+1],
                    o->vertex+3*o->face[3*i+2]);
      }
    printf("  vertex count=%d\n",o->vertexSize);
    printf("  face   count=%d\n",o->faceSize);
    return true;
}

/** @brief	Add objects to the scene
 *
 *	@param	int		id
 *	@param	Object*	o
 *
 *	@note
 */
bool AddObject(int id, Object* o, char*bvhFile=0)
{
    o->object=new SCObject();
    int result;
#if SC_MODE==SC_SCENE_MANAGER_CLOSED_POLYHEDRA
#ifdef USE_SPO
    // Use SmartPolygonOptimizer to add multiple boundary piece.
    printf("  SmartPolygonOptimizer ...\n");
    {
        SPOObject t;
        result=t.AddTriangles(o->vertex,o->vertexSize,
                              o->face,o->faceSize);
        if(result==SPO_ERROR_INVALID_LICENSE){
            printf("Error: Invalid license of SmartPolygonOptimizer\n");
            return false;
        }
        if(result!=SPO_NO_ERROR)
          {
              printf("Error: Failed to add triangles.\n");
              return false;
          }
        //t.ConnectVertices(0.0);
        t.ConnectVertices(0.0);
        t.DecomposeIntoSingleBoundaryPieces();
        //t.RemoveRedundantVertices(0.01,20);
        //t.RemoveThinTriangles(0.0,20);
        int i;
        printf("  piece  count=%d\n",t.GetPieceCount());
        for(i=0;i<t.GetPieceCount();i++){
            const SPOPiece*p=t.GetPiece(i);
            result=o->object->AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON,
                                           p->vertices,p->vertexSize,
                                           p->triangles,p->triangleSize);
            if(result!=SC_NO_ERROR)break;
        }
    }
#else
    result=o->object->AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON,
                                   o->vertex,o->vertexSize,
                                   o->face,o->faceSize, bvhFile);
#endif
#else

    printf("Object type: Triangle soup\n");
    result=o->object->AddTriangles(SC_OBJECT_TYPE_TRIANGLE_SOUP,
                                   o->vertex,o->vertexSize,
                                   o->face,o->faceSize);
#endif

    if(result==SC_ERROR_INVALID_LICENSE){
        printf("Error: Invalid license of SmartCollisionSDK\n");
        return false;
    }
    if(result!=0)
      {
          printf("Error:AddTriangles failed(%d)\n",result);
          return false;
      }
    o->id=id;				// Set ID
    o->controlledFlag=0;	// Set object not handled
    o->object->GetTransformation(SC_TRANSFORMATION_MATRIX,o->matrix);// Get the Default matrix
    result=manager.AddObject(o->id,o->object);
    if(result!=0)
      {
          printf("Error:AddObject failed(%d)\n",result);
          return false;
      }
    return true;
}

/** @brief	Load a scene
 *
 *	@param	int		argc
 *	@param	char*	argv[]
 *
 *	@note
 */
int LoadScene(int argc, char* argv[])
{
    if(argc<2)
      return -1;

    for(int i=1;i<argc;i++)
      {
          // Load objects from file
          if(LoadObject(object+objectSize,argv[i])==false)
            return -1;
          // Add them to the manager
          if(AddObject(10000-objectSize,object+objectSize)==false)
            return -1;
          objectSize++;
      }
    hapticPointerObject.id=100000;
    LoadObject(&hapticPointerObject,argv[1]);
    for(i=0;i<hapticPointerObject.vertexSize*3;i++)
      {
          hapticPointerObject.vertex[i]*=0.1;
      }
    return objectSize;
}

void GetBoundingBox(double b[6],double*vertex,int size)
{
    int i;
    b[0]=b[1]=vertex[0];
    b[2]=b[3]=vertex[1];
    b[4]=b[5]=vertex[2];
    for(i=1;i<size;i++)
      {
          double x,y,z;
          x=vertex[3*i+0];
          y=vertex[3*i+1];
          z=vertex[3*i+2];
          if(x<b[0])b[0]=x;else if(x>b[1])b[1]=x;
          if(y<b[2])b[2]=y;else if(y>b[3])b[3]=y;
          if(z<b[4])b[4]=z;else if(z>b[5])b[5]=z;
      }
}

void BoundingBoxSum(double b[6],const double c[6])
{
    if(c[0]<b[0])b[0]=c[0];
    if(c[1]>b[1])b[1]=c[1];
    if(c[2]<b[2])b[2]=c[2];
    if(c[3]>b[3])b[3]=c[3];
    if(c[4]<b[4])b[4]=c[4];
    if(c[5]>b[5])b[5]=c[5];
}

/** @brief	Configuration of SCSceneManager
 *
 *	@param
 *
 *	@note
 */
bool Setup()
{
    if(objectSize){
        // Specify the target object
        Object* o= object+1;
        // Get the bounding box of target object
        double b[6];
        int i;
        for(i=0;i<objectSize;i++){
            Object*o=object+i;
            // Get bounding box
            if(i==0){
              GetBoundingBox(b,o->vertex,o->vertexSize);
            }else{
                double t[6];
                GetBoundingBox(t,o->vertex,o->vertexSize);
                BoundingBoxSum(b,t);
            }
        }
        double t,max;
        t=b[1]-b[0];max=t;
        t=b[3]-b[2];if(t>max)max=t;
        t=b[5]-b[4];if(t>max)max=t;
        // Change Projection matrix by the size of model
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        double center[3];
        center[0]=(b[0]+b[1])*0.5;
        center[1]=(b[2]+b[3])*0.5;
        center[2]=(b[4]+b[5])*0.5;
        gluPerspective(30,(double)wx/(double)wy,1.0,3000.0);
        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(center[0],center[1],center[2]+max*3,
                  center[0],center[1],center[2],
                  0, 1, 0);
        glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
        scale=max*0.02;
        maxDistance=max;
        printf("center=(%g,%g,%g)\n",center[0],center[1],center[2]);
        printf("max=%g\n",max);
    }
    tolerance=scale*0.2;// Set the tolerance value 0.2[mm]
    printf("Scale=%lg\n",scale);
    printf("Tolerance: %lg(%lg[mm])\n",tolerance,tolerance/scale);
    printf("Max distance: %lg\n",maxDistance);
    manager.SetAttributeDouble(SC_SCENE_MANAGER_TOLERANCE,tolerance);
    manager.SetAttributeDouble(SC_SCENE_MANAGER_MAX_DISTANCE,maxDistance);
    manager.SetAttributeInteger(SC_SCENE_MANAGER_MAX_ITERATION,maxIteration);
    manager.SetAttributeDouble(SC_SCENE_MANAGER_FORCE_STIFFNESS,
                               forceStiffness/(scale*scale));
    manager.SetAttributeDouble(SC_SCENE_MANAGER_TORQUE_STIFFNESS,
                               torqueStiffness);

    if(AddObject(hapticPointerObject.id,&hapticPointerObject)==false)
      return false;

    manager.AddControlledObject(hapticPointerObject.id);
    device.SetScale(scale);

    return true;
}

/** @brief	Exit function
 *
 *	@param
 *
 *	@note	This is called when this application terminates
 */
void ExitFunction(void)
{
    printf("Stop device.\n");
    device.Stop();
}

/** @brief	Main function
 *
 *	@param	int		argc
 *	@param	char*	argv[]
 *
 *	@note
 */
int main(int argc, char* argv[])
{
    // ***Configuration of GLUT***
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wx,wy);
    glutCreateWindow("SmartCollision(TM) 3D Incorpolated");
    glutIdleFunc(Idle);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Key);
    glutMotionFunc(Motion);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    atexit(ExitFunction);

    char*version;
    manager.GetAttributeString(SC_VERSION,version);
    printf("SmartCollision Version %s\n",version);

    // ***Loading scene***
    if(LoadScene(argc,argv)<0)
      {
          printf("Error: Failed to load scene\n");
          printf("Press return to exit\n");
          char s[1000];gets(s);
          return -1;
      }
    // ***Configuration of SCSceneManager***
    Setup();

    // ***Configuration of Haptics***
    // Haptics Loop
    {
        PrintUsage();
        printf("\n");
        device.WaitForUserAdmit();
    }
    device.SetCollisionFunction(CollisionFunction,0);
    device.SetHapticFunction(HapticFunction,0);
    // ***Haptics Loop***
    device.Start();
    // ***Graphics Loop***
    glutMainLoop();

    return 0;
}
