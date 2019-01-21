#pragma once

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <string>
#include <vector>

template <class T>
class CSpidarEnhance;

#define XML_PARAM_MAX_NUM 64

typedef struct param_pair{
	std::string name;
	std::string value;
} ParamPair;

template <class T>
class CSpidarXMLHandler : public xercesc::DefaultHandler {
protected:
	CSpidarEnhance<T>* pSpidar;
	FILE* m_fp_log;

protected:
	std::string pos_unit;
	std::string ori_unit;
	std::string force_unit;
	std::string torque_unit;

protected:
	std::string spidar_type;
public:
	void GetSpidarType(std::string& str);

protected:
	ParamPair params[XML_PARAM_MAX_NUM];
	int params_num;

public:
	CSpidarXMLHandler(void);
	virtual ~CSpidarXMLHandler(void);
public:
	void init(CSpidarEnhance<T>* pObj,FILE* fp);

public:
	void startElement(const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname, const xercesc::Attributes& attrs);
	void endElement  (const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname);
	void characters(const XMLCh* const chars, const XMLSize_t length);
public:
	void error(const xercesc_3_0::SAXParseException &exc);
	void fatalError(const xercesc_3_0::SAXParseException &exc);
	void warning(const xercesc_3_0::SAXParseException &exc);

public:
	void exe_spidar_ahs(char* lname, const xercesc::Attributes& attrs);
	void exe_controller_type(char* lname, const xercesc::Attributes& attrs);
	void exe_spidar_type(char* lname, const xercesc::Attributes& attrs);
	void exe_vr_vs_device_scale(char* lname, const xercesc::Attributes& attrs);//
	void exe_imp_pset(char* lname, const xercesc::Attributes& attrs);//
	void exe_imp_qset(char* lname, const xercesc::Attributes& attrs);//
	void exe_control_type(char* lname, const xercesc::Attributes& attrs);
	void exe_mmt_msec(char* lname, const xercesc::Attributes& attrs);
	void exe_sh_spi_usec(char* lname, const xercesc::Attributes& attrs);
	void exe_sh_spi_mode(char* lname, const xercesc::Attributes& attrs);
	void exe_voice_navi(char* lname, const xercesc::Attributes& attrs);
	void exe_motor_connection(char* lname, const xercesc::Attributes& attrs);
	void exe_spidar_motor_definition(char* lname, const xercesc::Attributes& attrs);
	void exe_param(char* lname, const xercesc::Attributes& attrs);// ’Ç‰Á
	void exe_motor_pos(char* lname, const xercesc::Attributes& attrs);
	void exe_grip_pos(char* lname, const xercesc::Attributes& attrs);
	void exe_motor_force(char* lname, const xercesc::Attributes& attrs);
	void exe_motor_pwm(char* lname, const xercesc::Attributes& attrs);
	void exe_motor_pid_imp(char* lname, const xercesc::Attributes& attrs);
	void exe_motor_pid_adm(char* lname, const xercesc::Attributes& attrs);
	void exe_correction_targetForceOpen(char* lname, const xercesc::Attributes& attrs);
	void exe_correction_adc_to_force(char* lname, const xercesc::Attributes& attrs);

	void exe_controller_motor_definition(char* lname, const xercesc::Attributes& attrs);
	void exe_rotation_dir(char* lname, const xercesc::Attributes& attrs);
	void exe_pully(char* lname, const xercesc::Attributes& attrs);
	void exe_encoder(char* lname, const xercesc::Attributes& attrs);
	void exe_dc_motor(char* lname, const xercesc::Attributes& attrs);

public:
	void end_controller_motor_definition(char* lname);

public:
	static int ReplaceStr(std::string& str, const std::string& from, const std::string& to);
	double ReplaceStr_Math(std::string& str);

	int paramSort();
	void exchangeParam(ParamPair* n1,ParamPair* n2);
};
