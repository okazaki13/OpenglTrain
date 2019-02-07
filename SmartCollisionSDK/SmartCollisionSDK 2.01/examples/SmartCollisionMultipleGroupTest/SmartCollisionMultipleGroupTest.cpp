/*************************************************************************\

  Copyright (c) 2006 3D Inc.
  All Rights Reserved.

 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "EasyDevice.h"
#include "sc.h"

#ifdef USE_SPO
#include "spo.h"
#endif

#include "MathUtility.h"
#include "TemplateVector3.h"
#include "TemplateQuaternion.h"

typedef BTVector3<double> Vector3;
typedef BTQuaternion<double> Quaternion;
template<class T>
inline void Swap(T&a,T&b)
{
    T t;
    t=a;
    a=b;
    b=t;
}

template<class T>
inline T Min(T a,T b)
{
    return a<b?a:b;
}

template<class T>
inline T Max(T a,T b)
{
    return a>b?a:b;
}

// Definition of object class
struct Object{
    int id;						// Object ID for SCSceneManager
    int gid;					// Group ID for SCSceneManager
    SCObject*object;            // SmartColllision Object
    int controlledFlag;			// Flag for handling object
    // Information for drawing
    double matrix[16];			// Matrix
    double*vertex;				// Vertex array
    int vertexSize;				// Number of vertex
    int*face;					// Index array
    int faceSize;				// Number of triangle    
    double*normal;				// Normal vector

    Vector3 position;           // Position of object
    Quaternion orientation;     // Orientation of object
    Vector3 tpdv;               // Sum of TPDV
    Vector3 rpdv;               // Sum of RPDV
    int contactCount;           // Contact count
    int type;                   // Type of object
    int invalidFlag;            // Flag of invalid state    
};

struct Status{
    int result1;
    int result2;
    int id1,id2;
    int gid1,gid2;
    double distance1;
    double distance2;
    Vector3 point1;
    Vector3 point2;
    Vector3 spoint1;
    Vector3 spoint2;
    Vector3 tpdv1,rpdv1;
    Vector3 tpdv2,rpdv2;
    Vector3 normal1,normal2;
};

// Constructor of EasyDevice
EasyDevice device;

// Definition of SCSceneManager mode
//#define SC_MODE SC_SCENE_MANAGER_TRIANGLE_SOUP
#define SC_MODE SC_SCENE_MANAGER_CLOSED_POLYHEDRA

#if SC_MODE==SC_SCENE_MANAGER_CLOSED_POLYHEDRA
#  define OBJECT_TYPE SC_OBJECT_TYPE_CLOSED_POLYHEDRON
#else
#  define OBJECT_TYPE SC_OBJECT_TYPE_TRIANGLE_SOUP
#endif

#define POINTER_OBJECT_GID 10000
#define OBJECT_MAX 100
#define RESULT_MAX 100

// Constructor of SCSceneManager
static SCSceneManager manager(SC_MODE);

// Parameter of SCSceneManager
static double tolerance=1e-3;	   // Tolerance of penetration depth
static double maxDistance=1;	   // Maximum value of minimum disance calculation
static double forceStiffness=0.4e0;//Coefficient of spring stiffness[N/(mm)]
static double torqueStiffness=50;  //Coefficient of spring torque stiffness[N・m]
static int maxIteration=10;        //Maximum iteration number for collision calculation
static int rotationMode=3;		   // Current Rotation mode

// Statuses of collision loop
static int result=SC_NO_ERROR;       // Resutl of collision detection 
static double distance;              // Distance of controlled object
static Vector3 contactPosition;      // Contact position of controlled object
static Quaternion contactOrientation;// Contact orientation of controlled object

// Statuses of haptic loop
static Vector3 pointerPosition; 		 // Position of haptic pointer
static Quaternion pointerOrientation;	 // Orientation of haptic pointer
static double pointerMatrix[16];		 // Matrix of haptic pointer
static Vector3 hapticForce;              // Force for haptic device
static Vector3 hapticTorque;             // Torque for haptic device

// Parameters 
static int selectedGroupIndex=0;         // Index of selected group
static int connectFlag=0;                // Status Flag for object and haptic pointer
static int forceFlag=1;				     // Flag for outputting force and torque
static int displayContactObjectFlag=0;	 // Flag for displaying contact state

// Parameters from HapticFunction to CollisionFunction
static Vector3 lastPointerPosition;	     // Last position of haptic pointer
static Quaternion lastPointerOrientation;// Last orientation of haptic pointer
static double lastPointerMatrix[16];     // Last matrix of haptic pointer
static int buttonCount;                  // Counter of device button

// Parameters from CollisionFunction to HapticFunction
static double lastDistance;              // Last distance
static Vector3 lastContactPosition;      // Last contact position
static Quaternion lastContactOrientation;// Last contact orientation
static int lastResult=SC_ERROR_NO_RESULT;// Last resuts
static int setOrientationFlag;           // Flag to set orientation of device
static int disableForceFlag=1;           // Flag for disabling force

// Parameters for applying penulty force and torque
static int stopFlag=0;
static double maxVelocity=100.0; 	   // Maximum velocity of moving objects[mm/sec]
static double maxAngularVelocity=180.0;// Maximum angular velocity of moving objects[degree/sec]
static int moveFlag=1;				   // Flag for moving objects
static int arbitraryConnectFlag=1;

// Parameters for display
static Vector3 center;               // Center of scene
static int wx=1024,wy=768;           // Window size
static int wireFrameFlag=0;
static double areaSize;
static double max;
static double scale=1;               // Scale of haptic pointer Position
static double zoomScale=3;

// Temporary parameters for DrawScene
static Vector3 pointerPosition0;
static double displayPointerMatrix[16];     // matrix of haptic pointer for display
static Vector3 displayForce,displayTorque;
static Vector3 tpdv0,rpdv0;
static int resultCount0;
static Status*statuses0;

static Object object[OBJECT_MAX];
static int objectSize=0;
static Object pointerObject;
static Status statuses[RESULT_MAX];
static int resultCount;

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

bool MakeCoordinate(float m[16],
                    const Vector3&a,
                    const Vector3&ez0)
{
    double bodyLength;
    Vector3 ex,ey,ez;
    ez=ez0;
    bodyLength=ez.Norm();
    if(bodyLength==0)return false;
    ez*=1.0/bodyLength;
    ex.Set(1,0,0);ex-=ScalerProduct(ex,ez)*ez;
    if(ex.Norm()<1e-3){
        ex.Set(0,1,0);ex-=ScalerProduct(ex,ez)*ez;
    }
    ex.Normalize();
    VectorProduct(ey,ez,ex);
    m[0]=ex.x;m[4]=ey.x;m[ 8]=ez.x;m[12]=a.x;
    m[1]=ex.y;m[5]=ey.y;m[ 9]=ez.y;m[13]=a.y;
    m[2]=ex.z;m[6]=ey.z;m[10]=ez.z;m[14]=a.z;
    m[3]=   0;m[7]=   0;m[11]=   0;m[15]=1;
    return true;
}

void DrawCone(const Vector3&p,const Vector3&z,
              double base,double height,int slices,int stacks,
              const float c[4])
{
    glMaterialfv(GL_FRONT,GL_DIFFUSE,c);
    glMaterialfv(GL_BACK,GL_DIFFUSE,c);
    glPushMatrix();
    {
        float t[16];
        MakeCoordinate(t,p,z);
        glMultMatrixf(t);
    }
    glutSolidCone(base,height,slices,stacks);
    glPopMatrix();
}

/** @brief	Drawing Object
 *
 *	@param	Object*	o
 *	@param	float*	diffuse
 *	@param	double	scale=1
 *
 *	@note
 */
void DrawObject(Object*o,float*diffuse)
{
    if(wireFrameFlag==0) {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
        glMaterialfv(GL_BACK ,GL_DIFFUSE,diffuse);
    }
    int i;
    glBegin(GL_TRIANGLES);
    for(i=0;i<o->faceSize;i++) {
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

/** @brief	Get collision status from the SCSceneManager for display
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void GetCollisionStatusForDisplay(void*pData)
{
    resultCount0=resultCount;
    statuses0=new Status[resultCount0];
    int i;
    for(i=0;i<resultCount0;i++)statuses0[i]=statuses[i];
    tpdv0=0;
    rpdv0=0;
    if(selectedGroupIndex>=0) {
        tpdv0=object[selectedGroupIndex].tpdv;
        rpdv0=object[selectedGroupIndex].rpdv;
    }
    for(i=0;i<objectSize;i++) {
        object[i].object->GetTransformation(SC_TRANSFORMATION_MATRIX,
                                            object[i].matrix);
        manager.GetTransformation(object[i].gid,
                                  SC_POSITION_WORLD_CENTER,
                                  object[i].position);
    }
    pointerPosition0=lastPointerPosition;
    CopyVector(displayPointerMatrix,lastPointerMatrix,16);
}

/** @brief	Get haptic status from the SCSceneManager for display 
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void GetHapticStatusForDisplay(void*pData)
{
    //device.GetLastRawMatrix(pointerMatrix);
    displayForce=hapticForce;
    displayTorque=hapticTorque;
}

/** @brief	Draw whole the scene including haptic pointer
 *
 *	@param
 *
 *	@note
 */
void DrawScene(void)
{
    // Get the Result of collision calculation
    device.SetHapticStatusFunction(GetHapticStatusForDisplay);
    device.SetCollisionStatusFunction(GetCollisionStatusForDisplay);
    int i;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDepthFunc(GL_LEQUAL);
    // Set light in haptic pointer position
    {
        float t[4];
        t[0]=pointerPosition0[0];
        t[1]=pointerPosition0[1];
        t[2]=pointerPosition0[2];
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
    // Display force and torque
    {
        double s;
        glEnable(GL_LIGHTING);
        Vector3 t,z;
        if(displayForce.Norm()>0){
            float c[4]={1,1,1,1};
            s=1e1/scale;
            glDisable(GL_LIGHTING);
            glColor3f(c[0],c[1],c[2]);
            glBegin(GL_LINES);
            t=pointerPosition0;
            glVertex3d(t[0],t[1],t[2]);
            t+=displayForce*s;
            glVertex3d(t[0],t[1],t[2]);
            glEnd();
            glEnable(GL_LIGHTING);
            z=displayForce;
            z.Normalize();
            glMaterialfv(GL_FRONT,GL_DIFFUSE,c);
            glMaterialfv(GL_BACK,GL_DIFFUSE,c);
            DrawCone(t,z,1.0*scale,2.0*scale,16,1,c);
        }
        if(displayTorque.Norm()>0){
            float c[4]={1,0.5,0,1};
            glDisable(GL_LIGHTING);
            glColor3f(c[0],c[1],c[2]);
            glBegin(GL_LINES);
            s=1e1;
            t=pointerPosition0;
            glVertex3d(t[0],t[1],t[2]);
            t+=displayTorque*s;
            glVertex3d(t[0],t[1],t[2]);
            glEnd();
            z=displayTorque;
            z.Normalize();
            glEnable(GL_LIGHTING);
            glMaterialfv(GL_FRONT,GL_DIFFUSE,c);
            glMaterialfv(GL_BACK,GL_DIFFUSE,c);
            DrawCone(t,z,1.0*scale,2.0*scale,16,1,c);
        }
    }
    // display haptic pointer
    {
        glPushMatrix();
        glMultMatrixd(displayPointerMatrix);
        double d=areaSize*0.2;
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glColor3f(1,0,0);
        glVertex3f(-d,0,0);
        glVertex3f(d,0,0);
        glColor3f(0,1,0);
        glColor3f(0,1,0);
        glVertex3f(0,-d,0);
        glVertex3f(0,d,0);
        glColor3f(0,0,1);
        glColor3f(0,0,1);
        glVertex3f(0,0,-d);
        glVertex3f(0,0,d);
        glEnd();

        glEnable(GL_LIGHTING);
        float c[4]={1.0,0.5,0.0,1};
        if(pointerObject.invalidFlag){
            c[0]=1.0;
            c[1]=0.0;
            c[2]=1.0;
        }
        DrawObject(&pointerObject,c);

        glPopMatrix();
    }
    // Display objects
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
    float c[4];
    c[3]=1;
    for(i=0;i<objectSize;i++){
        Object*o=object+i;
        if(i==selectedGroupIndex){
            c[0]=0.0;
            c[1]=c[2]=1;
        } else if(o->invalidFlag){
            c[0]=1;
            c[1]=0;
            c[2]=1;
        } else {
            c[0]=c[1]=c[2]=0.8;
        }
        switch(o->type) {
          case SC_ACTIVITY_PASSIVE:
            c[0]*=0.5;
            c[1]*=0.5;
            c[2]=0.5;
            break;
          case SC_ACTIVITY_INACTIVE:
            c[0]*=0.2;
            c[1]*=0.2;
            c[2]=0.2;
            break;
        }
        // オブジェクトの表示
        glPushMatrix();
        if(connectFlag&&
           displayContactObjectFlag&&
           i==selectedGroupIndex) {
            Vector3 c;
            c=o->position-tpdv0;
            glTranslated(c[0],c[1],c[2]);
            glRotated(-rpdv0.Norm()*180.0/M_PI,
                      rpdv0[0],rpdv0[1],rpdv0[2]);
            c=o->position;
            glTranslated(-c[0],-c[1],-c[2]);
        }
        glMultMatrixd(o->matrix);
        if(wireFrameFlag) {
            glColor3f(c[0],c[1],c[2]);
            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        DrawObject(o,c);
        if(wireFrameFlag) {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glEnable(GL_LIGHTING);
        }
        glPopMatrix();
    }
    // Display results of collision detection
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    for(i=0;i<resultCount0;i++) {
        Status*t=statuses0+i;
        if(t->result1!=SC_NO_ERROR&&
           t->result2!=SC_NO_ERROR)continue;
        double u;
        u=Min(t->distance1,t->distance2)/maxDistance;
        //u=0.1;
        float c[4];
        if(u<0){
            c[0]=0;
            c[1]=0;
            c[2]=1;// blue
            c[3]=1;
        } else if(u<0.8) {
            u/=0.8;
            double v=1.0-u;
            c[0]=1.0*v+1.0*u;
            c[1]=0.0*v+1.0*u;
            c[2]=0.0*v+0.0*u;// between red and yellow
            c[3]=1.0;
        } else {
            u=(u-0.8)/0.2;
            c[0]=1.0;
            c[1]=1.0;
            c[2]=0.0;// yellow
            c[3]=1.0-u;
        }
        glDisable(GL_LIGHTING);
        glColor4f(c[0],c[1],c[2],c[3]);

        glBegin(GL_LINES);
        glVertex3d(t->point1[0],t->point1[1],t->point1[2]);
        glVertex3d(t->point2[0],t->point2[1],t->point2[2]);
        glEnd();
        //glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);

        //double as=1.0*scale;
        double as=1.0*areaSize*0.01;
        Vector3 m,z;
        z=t->point2-t->point1;
        z.Normalize();
        Vector3 a;
        a=t->point2-z*(as*2.0);
        c[0]=1.0;
        c[1]=0.0;
        c[2]=0.0;
        DrawCone(a,z,as,as*2.0,16,1,c);
        c[0]=0.0;
        c[1]=0.0;
        c[2]=1.0;
        z.Invert();
        a=t->point1-z*(as*2.0);
        DrawCone(a,z,as,as*2.0,16,1,c);

        glDisable(GL_LIGHTING);
    }
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    delete statuses0;
}

void Display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30,(double)wx/(double)wy,1.0,3000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(center[0],center[1],center[2]+max*zoomScale,
              center[0],center[1],center[2],
              0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    DrawScene();
    glFlush();
    glutSwapBuffers();
}

void PrintUsage(void)
{
    printf("Usage: SmartCollisionTest [glut options] file...\n");
    printf(" ' ': Connect the controlled object by its origin.\n");
    printf(" 'A': Activate all object.\n");
    printf(" 'a': Make the selected object active.\n");
    printf(" 'C': Toggle displaying contact state or not.\n");
    printf(" 'd': Make the selected object inactive.\n");
    printf(" 'p': Make the selected object passive.\n");
    printf(" 'f': Toggle force and torque feedback.\n");
    printf(" 'r': Change rotation mode.\n");
    printf(" 'q': Quit.\n");
    printf(" 'h': Print this message.\n");
    printf(" Touch object: Toggle controlled/static object.\n");
}

int GetObjectIndex(int gid)
{
    int i;
    for(i=0;i<objectSize;i++) {
        if(object[i].gid==gid) {
            return i;
        }
    }
    return -1;
}

void UpdateStatus(void)
{
    // Set attributes of SCSceneManager
    switch(rotationMode) {
      case 0:manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,SC_ROTATION_MODE_NONE );
        break;
      case 1:manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,SC_ROTATION_MODE_FREE );
        break;
      case 2:manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,SC_ROTATION_MODE_INPUT);
        break;
      case 3:manager.SetAttributeEnum(SC_SCENE_MANAGER_ROTATION_MODE,SC_ROTATION_MODE_MIX  );
        break;
    }
    // Update statuses
    manager.UpdateStatus();
    // Get statuses
    int i,n;
    double minDistance=tolerance;
    pointerObject.tpdv=0;
    pointerObject.rpdv=0;
    pointerObject.invalidFlag=0;
    for(i=0;i<objectSize;i++) {
        object[i].invalidFlag=0;
    }
    manager.GetStatus(SC_STATUS_COUNT,&n);
    resultCount=0;
    for(i=0;i<n;i++) {
        int gids[2];
        int result1,result2;
        manager.GetStatus(SC_GROUP_ID ,gids,i,false);
        manager.GetStatus(SC_STATUS_RESULT,&result1,i,false);
        manager.GetStatus(SC_STATUS_RESULT,&result2,i,true );
        double distance1=1e10,distance2=1e10;
        if(result1==SC_NO_ERROR){
            manager.GetStatus(SC_DISTANCE,&distance1,i,false);
        }else if(result1==SC_ERROR_INVALID_INITIAL_TRANSFORMATION){
            if(gids[0]==POINTER_OBJECT_GID){
                pointerObject.invalidFlag=1;
            }else{
                int j=GetObjectIndex(gids[0]);
                object[j].invalidFlag=1;
            }
        }
        if(result2==SC_NO_ERROR){
            manager.GetStatus(SC_DISTANCE,&distance2,i,true );
        }else if(result2==SC_ERROR_INVALID_INITIAL_TRANSFORMATION){
            if(gids[1]==POINTER_OBJECT_GID){
                pointerObject.invalidFlag=1;
            }else{
                int j=GetObjectIndex(gids[1]);
                object[j].invalidFlag=1;
            }
        }
        if(result1!=SC_NO_ERROR&&
           result2!=SC_NO_ERROR)continue;
        if(connectFlag==0){
            if(gids[0]==POINTER_OBJECT_GID){
                if(distance1<minDistance){
                    int j=GetObjectIndex(gids[1]);
                    if(j>=0) {
                        selectedGroupIndex=j;
                        minDistance=distance1;
                    }
                    if(distance1<=0){
                        Vector3 tpdv,rpdv;
                        manager.GetStatus(SC_TPD_VECTOR,tpdv,i,false);
                        manager.GetStatus(SC_RPD_VECTOR,rpdv,i,false);
                        pointerObject.tpdv+=tpdv;
                        pointerObject.rpdv+=rpdv;
                    }
                }
                continue;
            }
            if(gids[1]==POINTER_OBJECT_GID){
                if(distance2<minDistance){
                    int j=GetObjectIndex(gids[0]);
                    if(j>=0) {
                        selectedGroupIndex=j;
                        minDistance=distance2;
                    }
                    if(distance2<=0){
                        Vector3 tpdv,rpdv;
                        manager.GetStatus(SC_TPD_VECTOR,tpdv,i,true);
                        manager.GetStatus(SC_RPD_VECTOR,rpdv,i,true);
                        pointerObject.tpdv+=tpdv;
                        pointerObject.rpdv+=rpdv;
                    }
                }
                continue;
            }
        }
        Status*r=statuses+resultCount;
        r->result1=result1;
        r->result2=result2;
        r->gid1=gids[0];
        r->gid2=gids[1];
        r->id1=GetObjectIndex(gids[0]);
        r->id2=GetObjectIndex(gids[1]);
        r->distance1=distance1;
        r->distance2=distance2;
        if(result1==SC_NO_ERROR){
            manager.GetStatus(SC_TPD_VECTOR,r->tpdv1,i,false);
            manager.GetStatus(SC_RPD_VECTOR,r->rpdv1,i,false);
            manager.GetStatus(SC_CONTACT_NORMAL,r->normal1,i,false);
            manager.GetStatus(SC_POINT_ON_TARGET  ,r->point1,i,false);
            manager.GetStatus(SC_POINT_ON_OPPONENT,r->spoint1,i,false);
        }else{
            r->tpdv1[0]=r->tpdv1[1]=r->tpdv1[2]=0;
            r->rpdv1[0]=r->rpdv1[1]=r->rpdv1[2]=0;
            r->normal1[0]=r->normal1[1]=r->normal1[2]=0;
            manager.GetStatus(SC_POINT_ON_OPPONENT,r->point1,i,true);
            manager.GetStatus(SC_POINT_ON_TARGET  ,r->spoint1,i,true);
        }
        if(result2==SC_NO_ERROR){
            manager.GetStatus(SC_TPD_VECTOR,r->tpdv2,i,true);
            manager.GetStatus(SC_RPD_VECTOR,r->rpdv2,i,true);
            manager.GetStatus(SC_CONTACT_NORMAL   ,r->normal2,i,true);
            manager.GetStatus(SC_POINT_ON_TARGET  ,r->point2 ,i,true);
            manager.GetStatus(SC_POINT_ON_OPPONENT,r->spoint2,i,true);
        }else{
            r->tpdv2[0]=r->tpdv2[1]=r->tpdv2[2]=0;
            r->rpdv2[0]=r->rpdv2[1]=r->rpdv2[2]=0;
            r->normal2[0]=r->normal2[1]=r->normal2[2]=0;
            manager.GetStatus(SC_POINT_ON_OPPONENT,r->point2,i,false);
            manager.GetStatus(SC_POINT_ON_TARGET  ,r->spoint2,i,false);
        }
        resultCount++;
    }
}

void ApplyForceToObjects(void)
{
    int i;
    for(i=0;i<objectSize;i++){
        object[i].tpdv=0;
        object[i].rpdv=0;
        object[i].contactCount=0;
    }
    for(i=0;i<resultCount;i++){
        Status*s=statuses+i;
        int t1=s->id1;
        int t2=s->id2;
        if(statuses[i].result1==SC_NO_ERROR&&
           statuses[i].distance1<-tolerance){
            object[t1].contactCount++;
            object[t1].tpdv+=s->tpdv1;
            object[t1].rpdv+=s->rpdv1;
        }
        if(statuses[i].result2==SC_NO_ERROR&&
           statuses[i].distance2<-tolerance){
            object[t2].contactCount++;
            object[t2].tpdv+=s->tpdv2;
            object[t2].rpdv+=s->rpdv2;
        }
    }
    for(i=0;i<objectSize;i++){
        int cn=object[i].contactCount;
        if(cn>0){
            object[i].tpdv*=1.0/cn;
            object[i].rpdv*=1.0/cn;
        }
    }
    for(i=0;i<objectSize;i++){
        if(connectFlag&&i==selectedGroupIndex)continue;
        Vector3 p;
        Quaternion q;
        manager.GetTransformation(object[i].gid,SC_POSITION_WORLD_CENTER,p);
        manager.GetTransformation(object[i].gid,SC_ORIENTATION_QUATERNION,q);
        if(moveFlag){
            Vector3 t;
            t=object[i].tpdv;
            double t0;
            t0=t.Norm();
            t.Normalize();
            t*=Min(t0*0.5,maxVelocity*scale*1e-2);
            p-=t;

            t=object[i].rpdv;
            t0=t.Norm();
            t.Normalize();
            t*=Min(t0*0.5,maxAngularVelocity*M_PI/180.0*1e-2);
            q.DivideFromLeft(t);
        }
        q.Normalize();
        object[i].position=p;
        object[i].orientation=q;
        manager.SetTransformation(object[i].gid,SC_POSITION_WORLD_CENTER,p);
        manager.SetTransformation(object[i].gid,SC_ORIENTATION_QUATERNION,q);
    }
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

/** @brief	Setup an object
 *
 *	@param	Object*		o
 *	@param	itn fixFlag
 *
 *	@note
 */
int SetupObject(Object*o,int fixFlag=0)
{
    // Calculation of normal vector
    if(o->vertexSize>0) {
        o->normal=new double[o->faceSize*3];
        for(int i=0;i<o->faceSize;i++) {
            GetNormal(o->normal+3*i,
                      o->vertex+3*o->face[3*i+0],
                      o->vertex+3*o->face[3*i+1],
                      o->vertex+3*o->face[3*i+2]);
        }
    }
    o->type=SC_ACTIVITY_ACTIVE;
    o->tpdv=0;
    o->rpdv=0;
    o->contactCount=0;
    o->invalidFlag=0;
    return true;
}

/** @brief	Load objects from file
 *
 *	@param	Object*		o
 *	@param	const char* file
 *
 *	@note
 */
bool LoadObject(Object*o,const char*file)
{
    printf("Load object '%s'\n",file);
    FILE*fp;
    fp=fopen(file,"r");
    if(fp==NULL) {
        printf("Error: Failed to load %s\n",file);
        return false;
    }
    o->vertexSize=0;
    o->faceSize=0;
    // Count the number of vertex and the number of faces
    for(;;) {
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
    for(;;) {
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
                  o->vertex+3*i+2)==3) {
            i++;
        }
        int f[3];
        if(sscanf(s,"f %d %d %d",f+0,f+1,f+2)==3) {
            o->face[3*j+0]=f[0]-1;
            o->face[3*j+1]=f[1]-1;
            o->face[3*j+2]=f[2]-1;
            j++;
        }
    }
    fclose(fp);
    SetupObject(o);
    printf("  vertexSize=%d\n",o->vertexSize);
    printf("  faceSize=%d\n",o->faceSize);
    return true;
}

/** @brief	Add objects to the scene
 *
 *	@param	int		id
 *	@param	Object*	o
 *
 *	@note
 */
bool AddObject(int id,Object*o,char*bvhFile=0)
{
    o->object=new SCObject(OBJECT_TYPE);
    int result;
#ifdef USE_SPO
    // Use SmartPolygonOptimizer to add multiple boundary piece.
    {
        static char*version=0;
        if(version==0)
          {
              spoGetString(SPO_VERSION,version);
              printf("SmartPolygonOptimizer\r\n    Version %s\r\n",version);
              printf("  sizeof(SPOreal)=%d\n",sizeof(SPOreal));
          }
    }
    {
        SPOObject t;
        result=t.AddTriangles(o->vertex,o->vertexSize,
                              o->face,o->faceSize);
        if(result==SPO_ERROR_INVALID_LICENSE){
            printf("Error: Invalid license.\n");
            exit(-1);
        }
        if(result!=SPO_NO_ERROR){
            printf("Error: Failed to add triangles(%d).\n",result);
            exit(-1);
        }
        t.DecomposeIntoSingleBoundaryPieces();
        int i;
        for(i=0;i<t.GetPieceCount();i++){
            const SPOPiece*p=t.GetPiece(i);
            result=o->object->AddTriangles(p->vertices,p->vertexSize,
                                           p->triangles,p->triangleSize);
        }
    }
#else
    result=o->object->AddTriangles(o->vertex,o->vertexSize,
                                   o->face,o->faceSize);
#endif

    if(result==SC_ERROR_INVALID_LICENSE) {
        printf("Error:Invalid license\n");
        return false;
    }
    if(result!=0) {
        printf("Error:AddTriangles failed(%d)\n",result);
        return false;
    }
    o->id=id;				// Set ID
    o->controlledFlag=0;	// Set object not handled
    result=manager.AddObject(o->id,o->object);
    if(result!=0) {
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
    if(argc<2) {
        printf("Usage: SmartCollisionMultipleBodyTest obj1 obj2 ...\n");
        return -1;
    }
    int i;
    for(i=1;i<argc;i++) {
        // Load objects from file
        if(LoadObject(object+objectSize,argv[i])==false) {
            return -1;
        }
        // Add them to the manager
        if(AddObject(objectSize,object+objectSize)==false) {
            return -1;
        }
        objectSize++;
    }
    LoadObject(&pointerObject,argv[1]);
    for(i=0;i<pointerObject.vertexSize*3;i++) {
        pointerObject.vertex[i]*=0.1;
    }
    SetupObject(&pointerObject);
    if(AddObject(100000,&pointerObject)==false)
      return false;
    return objectSize;
}

/** @brief	Configuration of SCSceneManager
 *
 *	@param
 *
 *	@note
 */
bool Setup(void)
{
    if(objectSize) {
        double b[6];
        int i;
        for(i=0;i<objectSize;i++) {
            Object*o=object+i;
            // Get bounding box
            if(i==0)
              GetBoundingBox(b,o->vertex,o->vertexSize);
            else {
                double t[6];
                GetBoundingBox(t,o->vertex,o->vertexSize);
                BoundingBoxSum(b,t);
            }
        }
        double t;
        t=b[1]-b[0];max=t;
        t=b[3]-b[2];if(t>max)max=t;
        t=b[5]-b[4];if(t>max)max=t;
          
        printf("max=%lg\n",max);
        max*=1;
        areaSize=max*1;
        center[0]=(b[0]+b[1])*0.5;
        center[1]=(b[2]+b[3])*0.5;
        center[2]=(b[4]+b[5])*0.5;
        scale=max*0.02;
        maxDistance=max*0.5;
    }
    tolerance=scale*0.2;
    if(maxDistance==0)maxDistance=tolerance*5e2;

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
    int i,result;
    for(i=0;i<objectSize;i++) {
        object[i].gid=10*i+1;
        result=manager.AddObjectToGroup(object[i].gid,object[i].id);
        if(result!=SC_NO_ERROR) {
            printf("Error: AddObjectToGroup failed(%d)\n",result);
            exit(-1);
        }
        Vector3 p;
        p=0;
        p[0]=-areaSize*0.3+areaSize*0.6*i/objectSize;
        manager.SetTransformation(object[i].gid,
                                  SC_POSITION_WORLD_CENTER,
                                  p);
        object[i].position=p;
        object[i].orientation.Identity();
    }
    pointerObject.gid=POINTER_OBJECT_GID;
    result=manager.AddObjectToGroup(pointerObject.gid,
                                    pointerObject.id);
                                       
    if(result!=SC_NO_ERROR) {
        printf("Error: AddObjectToGroup failed(%d)\n",result);
        exit(-1);
    }
    device.SetScale(scale);
    return true;
}

void ToggleConnect(void)
{
    if(selectedGroupIndex<0)return;
    result=SC_ERROR_NO_RESULT;
    Vector3 p;
    Quaternion q;
    connectFlag^=1;
    Object*o=object+selectedGroupIndex;
    manager.GetTransformation(o->gid,SC_POSITION_WORLD_CENTER,p);
    manager.GetTransformation(o->gid,SC_ORIENTATION_QUATERNION,q);
    if(connectFlag==0) {
        if(displayContactObjectFlag) {
            p-=o->tpdv;
            q.DivideFromLeft(o->rpdv);
            q.Normalize();
            manager.SetTransformation(o->gid,SC_POSITION_WORLD_CENTER,p);
            manager.SetTransformation(o->gid,SC_ORIENTATION_QUATERNION,q);
        }
        if(arbitraryConnectFlag) {
            p=0;
            manager.SetTransformation(o->gid,SC_POSITION_NEW_LOCAL_CENTER,p);
        }
        manager.SetTransformation(POINTER_OBJECT_GID,SC_POSITION_WORLD_CENTER,
                                  pointerPosition);
        manager.SetTransformation(POINTER_OBJECT_GID,SC_ORIENTATION_QUATERNION,
                                  pointerOrientation);
        manager.SetActivityGroup(pointerObject.gid,SC_ACTIVITY_ACTIVE);
    } else {
        pointerOrientation=q;
        setOrientationFlag=1;
        manager.SetActivityGroup(pointerObject.gid,SC_ACTIVITY_INACTIVE);
        if(arbitraryConnectFlag) {
            manager.SetTransformation(o->gid,SC_POSITION_NEW_WORLD_CENTER,
                                      pointerPosition);
                                      
        }
    }
    disableForceFlag=1;
}

void GetContactTransformation(double cp[3],double cq[4],
                              const double p   [3],const double q   [4],
                              const double tpdv[3],const double rpdv[3])
{
    cp[0]=p[0]-tpdv[0];
    cp[1]=p[1]-tpdv[1];
    cp[2]=p[2]-tpdv[2];
    double rpdq[4];
    FromVectorToQuaternion(rpdq,rpdv);
    InvertQuaternion(rpdq);
    MultiplyQuaternion(cq,rpdq,q);
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
    if(selectedGroupIndex>=0&&buttonCount>0){
        buttonCount--;
        ToggleConnect();
    }
    lastPointerPosition=pointerPosition;
    lastPointerOrientation=pointerOrientation;
    lastResult=result;
    CopyVector(lastPointerMatrix,pointerMatrix,16);
}

/** @brief	Set haptic status
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void SetHapticStatus(void*pData)
{
    lastContactPosition=contactPosition;
    lastContactOrientation=contactOrientation;
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
    // (1) Get haptic status
    device.SetHapticStatusFunction(GetHapticStatus,0);
    // (2) Set transformation of haptic pointer or selected group to the SCSceneManager
    Object*o=0;
    if(connectFlag==0){
        o=&pointerObject;
    }else if(selectedGroupIndex>=0){
        o=object+selectedGroupIndex;
    }
    if(o){
        manager.SetTransformation(o->gid,SC_POSITION_WORLD_CENTER,lastPointerPosition);
        manager.SetTransformation(o->gid,SC_ORIENTATION_QUATERNION,lastPointerOrientation);
    }
    if(stopFlag==0){
        // (3) Update status of collision calculation
        UpdateStatus();
        // (4) Apply penulty force to each object
        ApplyForceToObjects();
    }
    // Store results of collisin detection
    if(o->invalidFlag==0){
        GetContactTransformation(contactPosition,
                                 contactOrientation,
                                 lastPointerPosition,
                                 lastPointerOrientation,
                                 o->tpdv,
                                 o->rpdv);
        if(o->tpdv.Norm()>0||o->tpdv.Norm()>0){
            distance=-1;
        }else{
            distance=1;
            disableForceFlag=0;
        }
        result=SC_NO_ERROR;
    }else{
        result=SC_ERROR_INVALID_INITIAL_TRANSFORMATION;
    }
    // (6) Set haptic status
    device.SetHapticStatusFunction(SetHapticStatus,0);
}

/** @brief	Haptics Loop
 *
 *	@param
 *
 *	@note	This should be called as CALLBACK
 */
void HapticFunction(void*data)
{
    if(setOrientationFlag){
        device.SetOrientation(pointerOrientation);
        setOrientationFlag=0;
    }
    // (1) Get direction and position of Haptic pointer
    device.GetPosition(pointerPosition);
    device.GetOrientation(pointerOrientation);
    device.GetLastRawMatrix(pointerMatrix);
    if(device.GetButton(0)==EH_BUTTON_DOWN){
          buttonCount++;
    }

    // (2) Configuration of force and torque
    Vector3 force(0.0,0.0,0.0);
    Vector3 torque(0.0,0.0,0.0);
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
    hapticForce=force;
    hapticTorque=torque;    
    device.SetForce(force);
    device.SetTorque(torque);
}

/** @brief	Idle function
 *
 *	@param
 *
 *	@note	This is called from GLUT
 */
void Idle(void)
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
void Mouse(int button,int state, int x, int y)
{
    if(button==GLUT_RIGHT_BUTTON) {
        if(state==GLUT_DOWN)
          device.MouseFunction(EH_RIGHT_BUTTON,EH_DOWN,x,y);
        else if(state==GLUT_UP)
          device.MouseFunction(EH_RIGHT_BUTTON,EH_UP,x,y);
    } else if(button==GLUT_LEFT_BUTTON) {
        if(state==GLUT_DOWN)
          device.MouseFunction(EH_LEFT_BUTTON,EH_DOWN,x,y);
        else if(state==GLUT_UP)
          device.MouseFunction(EH_LEFT_BUTTON,EH_UP,x,y);
    } else if(button==GLUT_MIDDLE_BUTTON) {
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
void KeyOperate(unsigned char key, int status,void*pData)
{
    switch(key){
      case 'S':
        stopFlag^=1;
        break; 
      case 'w':
        wireFrameFlag^=1;
        break;
      case 'C':
        displayContactObjectFlag^=1;
        break;
      case 'f':
        forceFlag^=1;
        printf("Force: %s\n",forceFlag?"on":"off");
        break;
      case 'm':
        moveFlag^=1;
        printf("Move: %s\n",moveFlag?"on":"off");
        break;
      case 'A':{// Activate all objects
          for(int i=0;i<objectSize;i++) {
              manager.SetActivityGroup(object[i].gid,SC_ACTIVITY_ACTIVE);
              object[i].type=SC_ACTIVITY_ACTIVE;
          }
          printf("Make all objects active\n");
          break;
      }
      case 'a':// Activate the selected object
        if(selectedGroupIndex<0)break;
        manager.SetActivityGroup(object[selectedGroupIndex].gid,SC_ACTIVITY_ACTIVE);
        object[selectedGroupIndex].type=SC_ACTIVITY_ACTIVE;
        printf("Make the selected object(%d) active\n",object[selectedGroupIndex].gid);
        break;
      case 'd':// Deactivate the selected object
        if(selectedGroupIndex<0)break;
        manager.SetActivityGroup(object[selectedGroupIndex].gid,SC_ACTIVITY_INACTIVE);
        object[selectedGroupIndex].type=SC_ACTIVITY_INACTIVE;
        printf("Make the selected object(%d) inactive\n",object[selectedGroupIndex].gid);
        break;
      case 'p':// Set the selected object passive
        if(selectedGroupIndex<0)break;
        manager.SetActivityGroup(object[selectedGroupIndex].gid,SC_ACTIVITY_PASSIVE);
        object[selectedGroupIndex].type=SC_ACTIVITY_PASSIVE;
        printf("Make the selected object(%d) passive\n",object[selectedGroupIndex].gid);
        break;
      case 'r': {// Change rotation mode
          rotationMode++;
          if(rotationMode>3)rotationMode=0;
          const char*s="";
          switch(rotationMode){
            case 0:s="None" ;break;
            case 1:s="Free" ;break;
            case 2:s="Input";break;
            case 3:s="Mix"  ;break;
          }
          printf("Rotation mode: %s\n",s);
          break;
      }
      case ' ':
        ToggleConnect();
        break;
      case 'h':
        PrintUsage();
        break;
      case 'q':
        exit(0);
        break;
    }
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
    device.SetKeyboardFunction(KeyOperate,key,0,0);
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
    wx=w;
    wy=h;
    glViewport(0, 0, w, h);
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
    //glutInitWindowPosition(0, 0);
    glutInitWindowSize(wx,wy);
    glutCreateWindow("SmartCollisionMultipleGroupTest");
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
    if(LoadScene(argc,argv)<0) {
        printf("Error: Failed to load scene\n");
        return -1;
    }
    // ***Configuration of SCSceneManager***
    Setup();

    // ***Configuration of Haptics***
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
