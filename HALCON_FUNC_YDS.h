
//简介： HALCON 12 中功能实现类 
//类名： HALCON_FUNC_YDS
//时间： 2016.10.26


#pragma once
#include "afxwin.h"
#include "HalconCpp.h"

typedef void NON_RETURN ;
typedef bool  BOOL_FLAG;
using namespace HalconCpp;



class HALCON_FUNC_YDS
{
public:

	HObject  ho_IMAGE_OF_INIT, ho_IMAGE_OF_INIT_jiazaizhng;      // init image
	HObject  ho_ROI_0;             // ncc region
	HObject  ho_ImageReduced;     
	HObject  ho_Image_temp;         // 相机返回数据
	HObject  ho_Circle;            //  芯片凹点的 REGION
	HObject  ho_Image_temp_corp;     // 芯片的印书体截图
	HObject  ho_Image_temp_Mean;      // 模糊 
	HObject  ho_Region_temp_DynThresh;    // 分割图像 by  阈值
	HObject  ho_Region_temp_Closing; 
	HObject  ho_ConnectedRegions;
	HObject  ho_SelectedRegions_char;
	HObject  ho_SelectedRegions_logo;
	HObject  ho_CharsSorted;
	HObject  ho_Characters;
	HObject  ho_RegionDilation;
	HObject  ho_Image_temp_logo;
	HObject  ho_RegionAffineTrans;    // 仿射变换的 REGION

	//相机相关的定义
	HTuple  hv_AcqHandle_of_camera, hv_Width_of_window, hv_Height_of_window;
	//图片的路径
	HTuple  hv_PATH_OF_PICTURE1, hv_PATH_OF_PICTURE2, hv_PATH_OF_PICTURE3;
	HTuple  hv_PATH_OF_PICTURE4, hv_PATH_OF_PICTURE5, hv_PATH_OF_PICTURE6;
	HTuple  hv_PATH_OF_PICTURE7;
	//标志位定义
	HTuple  hv_FLAG_ING_ADJUST_YES_OR_NO_YDS, hv_FLAG_ING_RECOGNIYION_YES_OR_NO_YDS;
	//NCC相关的定义
	HTuple  hv_ColumnRef, hv_ModelID, hv_Rows, hv_Cols, hv_Area, hv_RowRef, hv_Row;
	HTuple  hv_Column, hv_Angle, hv_Score, hv_HomMat2D;
	//正确数据的备份的定义
	HTuple  hv_RowEdgeFirst1_last, hv_ColumnEdgeFirst1_last;
	HTuple  hv_AmplitudeFirst1_last, hv_RowEdgeSecond1_last;
	HTuple  hv_ColumnEdgeSecond1_last, hv_AmplitudeSecond1_last;
	HTuple  hv_PinWidth1_last, hv_PinDistance1_last, hv_RowEdgeFirst2_last;
	HTuple  hv_ColumnEdgeFirst2_last, hv_AmplitudeFirst2_last;
	HTuple  hv_RowEdgeSecond2_last, hv_ColumnEdgeSecond2_last;
	HTuple  hv_AmplitudeSecond2_last, hv_PinWidth2_last, hv_PinDistance2_last;
	//HALCON窗口的句柄
	HTuple  hv_WindowHandle;
	//HTuple  ho_RegionAffineTrans;
	//芯片凹点位置信息
	HTuple  hv_point_yds_row;
	HTuple  hv_point_yds_col, hv_point_yds_row_crop, hv_point_yds_column_crop;
	//印刷体截图尺寸
	HTuple  hv_point_yds_width_crop, hv_point_yds_height_crop;
	// LOGO的相关定义
	HTuple  hv_point_yds_row_logo, hv_point_yds_column_logo;
	HTuple  hv_point_yds_width_logo, hv_point_yds_height_logo;
	//芯片管脚的矩形数据
	HTuple  hv_point_yds_row1, hv_point_yds_column1, hv_point_yds_phi1;
	HTuple  hv_point_yds_Length1, hv_point_yds_Length2, hv_point_yds_row2;
	HTuple  hv_point_yds_column2, hv_point_yds_phi2, hv_point_yds_row3;
	HTuple  hv_point_yds_column3, hv_point_yds_phi3, hv_point_yds_Length3;
	HTuple  hv_point_yds_Length4, hv_point_yds_Length5, hv_point_yds_Length6;

	//管脚新增的变量
	HTuple  hv_point_yds_row11, hv_point_yds_column11, hv_point_yds_phi11;
	HTuple  hv_point_yds_row12, hv_point_yds_column12, hv_point_yds_phi12;
	HTuple  hv_point_yds_row13, hv_point_yds_column13, hv_point_yds_phi13;
	HTuple  hv_point_yds_row14, hv_point_yds_column14, hv_point_yds_phi14;
	HTuple  hv_point_yds_row15, hv_point_yds_column15, hv_point_yds_phi15;
	HTuple  hv_point_yds_row16, hv_point_yds_column16, hv_point_yds_phi16;
	HTuple  hv_point_yds_row17, hv_point_yds_column17, hv_point_yds_phi17;
	HTuple  hv_point_yds_row18, hv_point_yds_column18, hv_point_yds_phi18;
	HTuple  hv_point_yds_row5, hv_point_yds_column5, hv_point_yds_phi5;
	HTuple  hv_point_yds_row4, hv_point_yds_column4, hv_point_yds_phi4;
	HTuple  hv_MeasureHandle4, hv_MeasureHandle5;
	HTuple  hv_MeasureHandle11, hv_MeasureHandle12;
	HTuple  hv_MeasureHandle13, hv_MeasureHandle14;
	HTuple  hv_MeasureHandle15, hv_MeasureHandle16;
	HTuple  hv_MeasureHandle17, hv_MeasureHandle18;
	HTuple  hv_ANGLE_OF_PIN1, hv_ANGLE_OF_PIN2, hv_ANGLE_OF_PIN3;
	HTuple  hv_ANGLE_OF_PIN4, hv_ANGLE_OF_PIN5, hv_ANGLE_OF_PIN6;
	HTuple  hv_ANGLE_OF_PIN7, hv_ANGLE_OF_PIN8, hv_ANGLE_OF_INC_PIN1;
	HTuple  hv_ANGLE_OF_INC_PIN2, hv_ANGLE_OF_INC_PIN3, hv_ANGLE_OF_INC_PIN4;
	HTuple  hv_ANGLE_OF_INC_PIN8, hv_ANGLE_OF_INC_PIN7, hv_ANGLE_OF_INC_PIN6;
	HTuple  hv_ANGLE_OF_INC_PIN5, hv_CURVA_DISTANCE_OF_PIN1;
	HTuple  hv_CURVA_DISTANCE_OF_PIN2, hv_CURVA_DISTANCE_OF_PIN3;
	HTuple  hv_CURVA_DISTANCE_OF_PIN4, hv_CURVA_DISTANCE_OF_PIN5;
	HTuple  hv_CURVA_DISTANCE_OF_PIN6, hv_CURVA_DISTANCE_OF_PIN7;
	HTuple  hv_CURVA_DISTANCE_OF_PIN8, hv_CURVA_DISTANCE_OF_INC_PIN1;
	HTuple  hv_CURVA_DISTANCE_OF_INC_PIN2, hv_CURVA_DISTANCE_OF_INC_PIN3;
	HTuple  hv_CURVA_DISTANCE_OF_INC_PIN4, hv_CURVA_DISTANCE_OF_INC_PIN5;
	HTuple  hv_CURVA_DISTANCE_OF_INC_PIN6, hv_CURVA_DISTANCE_OF_INC_PIN7;
	HTuple  hv_CURVA_DISTANCE_OF_INC_PIN8;
	HTuple  hv_RowEdgeFirst4;
	HTuple  hv_ColumnEdgeFirst4, hv_AmplitudeFirst4, hv_RowEdgeSecond4;
	HTuple  hv_ColumnEdgeSecond4, hv_AmplitudeSecond4, hv_PinWidth4;
	HTuple  hv_PinDistance4, hv_RowEdgeFirst5, hv_ColumnEdgeFirst5;
	HTuple  hv_AmplitudeFirst5, hv_RowEdgeSecond5, hv_ColumnEdgeSecond5;
	HTuple  hv_AmplitudeSecond5, hv_PinWidth5, hv_PinDistance5;
	HTuple  hv_RowEdge11, hv_Distance11;
	HTuple  hv_RowEdge12, hv_Distance12, hv_RowEdge13, hv_Distance13;
	HTuple  hv_RowEdge14, hv_Distance14, hv_RowEdge15, hv_Distance15;
	HTuple  hv_RowEdge16, hv_Distance16, hv_RowEdge17, hv_Distance17;
	HTuple  hv_RowEdge18, hv_Distance18, hv_SPAN_OF_CHIP_1;
	HTuple  hv_SPAN_OF_CHIP_2, hv_SPAN_OF_CHIP_3, hv_SPAN_OF_CHIP_4;

	//芯片管脚的测量句柄
	HTuple  hv_MeasureHandle1, hv_MeasureHandle2;
	HTuple  hv_MeasureHandle3, hv_RowEdge, hv_ColumnEdge, hv_Amplitude;
	HTuple  hv_Distance, hv_PinHeight1, hv_PinHeight2, hv_PinHeight3;
	HTuple  hv_n, hv_Seconds1, hv_i, hv_RowEdgeFirst1, hv_ColumnEdgeFirst1;
	HTuple  hv_AmplitudeFirst1, hv_RowEdgeSecond1, hv_ColumnEdgeSecond1;
	HTuple  hv_AmplitudeSecond1, hv_PinWidth1, hv_PinDistance1;
	HTuple  hv_RowEdgeFirst2, hv_ColumnEdgeFirst2, hv_AmplitudeFirst2;
	HTuple  hv_RowEdgeSecond2, hv_ColumnEdgeSecond2, hv_AmplitudeSecond2;
	HTuple  hv_PinWidth2, hv_PinDistance2, hv_shuzuyuansu_geshu;

	HTuple  hv_Seconds2, hv_Time, hv_avgPinWidth1, hv_avgPinDistance1;
	HTuple  hv_numPins1, hv_avgPinWidth2, hv_avgPinDistance2;
	HTuple  hv_numPins2, hv_avgPinDistance, hv_avgPinWidth, hv_pin_differ, hv_dis_differ;
	HTuple  hv_numPins, hv_Sigma, hv_Threshold, hv_Transition;
	HTuple  hv_Select, hv_Offset_dyn_threshod, hv_Radius_closing_circle;
	HTuple  hv_Index, hv_RowCh, hv_ColumnCh, hv_Class, hv_Area1;
	HTuple  hv_IndexL, hv_TmpDir, hv_TrainFile, hv_TrainFileBig;

	BOOL_FLAG Result_detection_00_00_YDS = 0;
	BOOL_FLAG Result_detection_01_00_YDS = 0;
	BOOL_FLAG Result_detection_02_00_YDS = 0;
	BOOL_FLAG Result_detection_03_00_YDS = 0;
	BOOL_FLAG Result_detection_04_00_YDS = 0;
	BOOL_FLAG Result_detection_10_00_YDS = 0;
	BOOL_FLAG Result_detection_11_00_YDS = 0;
	BOOL_FLAG Result_detection_12_00_YDS = 0;
	BOOL_FLAG Result_detection_13_00_YDS = 0;
	BOOL_FLAG Result_detection_14_00_YDS = 0;
	BOOL_FLAG Result_detection_15_00_YDS = 0;
	BOOL_FLAG Result_detection_16_00_YDS = 0;
	BOOL_FLAG Result_detection_17_00_YDS = 0;
	BOOL_FLAG Result_detection_18_00_YDS = 0;
	BOOL_FLAG Result_detection_19_00_YDS = 0;
	BOOL_FLAG Result_detection_20_00_YDS = 0;
	BOOL_FLAG Result_detection_21_00_YDS = 0;
	BOOL_FLAG Result_detection_25_00_YDS = 0;
	BOOL_FLAG Result_detection_29_00_YDS = 0;
	BOOL_FLAG Result_detection_24_01_YDS = 0;
	BOOL_FLAG Result_detection_24_02_YDS = 0;
	BOOL_FLAG Result_detection_24_03_YDS = 0;
	BOOL_FLAG Result_detection_24_04_YDS = 0;
	BOOL_FLAG Result_detection_24_05_YDS = 0;
	BOOL_FLAG Result_detection_24_06_YDS = 0;
	BOOL_FLAG Result_detection_24_07_YDS = 0;
	BOOL_FLAG Result_detection_24_08_YDS = 0;
	BOOL_FLAG Result_detection_26_01_YDS = 0;
	BOOL_FLAG Result_detection_26_02_YDS = 0;
	BOOL_FLAG Result_detection_26_03_YDS = 0;
	BOOL_FLAG Result_detection_26_04_YDS = 0;
	BOOL_FLAG Result_detection_26_05_YDS = 0;
	BOOL_FLAG Result_detection_26_06_YDS = 0;
	BOOL_FLAG Result_detection_26_07_YDS = 0;
	BOOL_FLAG Result_detection_26_08_YDS = 0;

	// 计算数据的返回
	CString  strBuffer_Result_dis_01_yds_width;
	CString  strBuffer_Result_dis_02_yds_width;
	CString  strBuffer_Result_dis_03_yds_width;
	CString  strBuffer_Result_dis_04_yds_width;
	CString  strBuffer_Result_dis_05_yds_width;
	CString  strBuffer_Result_dis_06_yds_width;
	CString  strBuffer_trans_hv_numPins;
	CString  strBuffer_trans_hv_PinWidth01;
	CString  strBuffer_trans_hv_PinWidth02;
	CString  strBuffer_trans_hv_PinWidth03;
	CString strBuffer_trans_hv_PinWidth04;
	CString strBuffer_trans_hv_PinWidth05;
	CString strBuffer_trans_hv_PinWidth06;
	CString strBuffer_trans_hv_PinWidth07;
	CString strBuffer_trans_hv_PinWidth08;
	CString strBuffer_trans_hv_gapWidth01;
	CString strBuffer_trans_hv_gapWidth02;
	CString strBuffer_trans_hv_gapWidth03;
	CString strBuffer_trans_hv_gapWidth04;
	CString strBuffer_trans_hv_gapWidth05;
	CString strBuffer_trans_hv_gapWidth06;
	CString strBuffer_trans_hv_gapWidth0a;
	CString strBuffer_trans_hv_PinWidth0a;
	CString Result_of_ocr_recognition;
	CString strBuffer_NCC_QUALITY_SCORE;
	CString strBuffer_OCV_QUALITY_SCORE_TRAIN;
	CString strBuffer_OCV_QUALITY_SCORE;
	CString strBuffer_OCV_QUALITY_SCORE_TRAIN_CAPSULE;
	CString strBuffer_OCV_QUALITY_SCORE_CAPSULE;

	CString strBuffer_hv_Distance11;
	CString strBuffer_hv_Distance12;
	CString strBuffer_hv_Distance13;
	CString strBuffer_hv_Distance14;
	CString strBuffer_hv_Distance15;
	CString strBuffer_hv_Distance16;
	CString strBuffer_hv_Distance17;
	CString strBuffer_hv_Distance18;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN1;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN2;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN3;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN4;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN5;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN6;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN7;
	CString strBuffer_hv_CURVA_DISTANCE_OF_PIN8;
	CString strBuffer_hv_CURVA_DISTANCE_OF_INC_PIN1;
	CString strBuffer_hv_SPAN_OF_CHIP_1;


	/////////////////////////////////////////////////OCR的相关变量的定义///////////////////////////////////////
	// Local iconic variables
	HObject  ho_Image;
	//HObject  ho_Region_temp_Closing, ho_ConnectedRegions, ho_SelectedRegions_char;
	//HObject  ho_CharsSorted, ho_Characters, ho_ROI_0, ho_RegionDilation;
	HObject  ho_ObjectSelected_temp, ho_CharacterSelected;

	// Local control variables
	HTuple  hv_Pointer, hv_Type, hv_Width, hv_Height;
	HTuple  hv_Classifier_svm_Az09, hv_Number_sop_8_num1;
	HTuple  hv_Rank_sop_8_num1, hv_ObjectSelected_all;
	HTuple  hv_Index_one_cc, hv_Width1, hv_Height1;
	HTuple  hv_Index_Offset_dyn_threshod;
	HTuple  hv_Index_Radius_closing_circle;
	HTuple  hv_Index_one, hv_sum_of_RowCh_and_ColumnCh, hv_Index_two;
	HTuple  hv_count;
	HTuple  hv_NumberObjects, hv_Index_two_cc, hv_CharacterNames;
	HTuple  hv_NumberCharacters, hv_index_one, hv_OCRHandle;
	HTuple  hv_OCRHandleReduced, hv_FileExists, hv_CharacterCount;
	HTuple  hv_FontFile, hv_Index_three, hv_Confidence;
	HTuple hv_NUMBER_RECOGNITION_ALL_CHAR;
	HTuple hv_NUMBER_RECOGNITION_FIR_CHAR;
	HTuple hv_NUMBER_RECOGNITION_SEC_CHAR;
	HTuple hv_NUMBER_RECOGNITION_THR_CHAR;


	//ocv
	HObject  ho_Image_temp_corp_init_ocv, ho_ROI_0_init_ocv;
	HObject  ho_ImageReduced_init_ocv, ho_Image_temp_corp_train_ocv;
	HObject  ho_ImageTrans_train_ocv, ho_MeanImage_TRAIN_OCV;
	HObject  ho_VarImage_TRAIN_OCV, ho_Image_temp_corp_OCV, ho_ImageTrans_ocv;
	HObject  ho_RegionDiff_ocv, ho_ConnectedRegions_ocv, ho_RegionsError_ocv, ho_ImageReduced_ocv;
	HTuple  hv_Pointer_ocv, hv_Type_ocv, hv_Width_ocv, hv_Height_ocv;
	HTuple  hv_Area_init_ocv, hv_RowRef_init_ocv, hv_ColumnRef_init_ocv;
	HTuple  hv_ShapeModelID_OVC, hv_VariationModelID_OCV, hv_I;
	HTuple  hv_Row_train_ocv, hv_Column_train_ocv, hv_Angle_train_ocv;
	HTuple  hv_Score_train_ocv=0, hv_HomMat2D_train_ocv, hv_Row_ocv;
	HTuple  hv_Column_ocv, hv_Angle_ocv, hv_Score_ocv=0, hv_HomMat2D_OCV;
	HTuple  hv_NumError_ocv;

	HObject  ho_Image_temp_corp_init_ocv_CAPSULE;
	HObject  ho_ROI_0_init_ocv_CAPSULE, ho_ImageReduced_init_ocv_CAPSULE;
	HObject  ho_Image_temp_corp_train_ocv_CAPSULE, ho_ImageTrans_train_ocv_CAPSULE;
	HObject  ho_MeanImage_TRAIN_OCV_CAPSULE, ho_VarImage_TRAIN_OCV_CAPSULE;
	HObject  ho_Image_temp_corp_OCV_CAPSULE, ho_ImageTrans_ocv_CAPSULE;
	HObject  ho_ImageReduced_ocv_CAPSULE, ho_RegionDiff_ocv_CAPSULE;
	HObject  ho_ConnectedRegions_ocv_CAPSULE, ho_RegionsError_ocv_CAPSULE;
	// OCV
	HTuple  hv_Pointer_CAPSULE, hv_Type_CAPSULE, hv_Width_CAPSULE;
	HTuple  hv_Height_CAPSULE, hv_Area_init_ocv_CAPSULE, hv_RowRef_init_ocv_CAPSULE;
	HTuple  hv_ColumnRef_init_ocv_CAPSULE, hv_ShapeModelID_OVC_CAPSULE;
	HTuple  hv_VariationModelID_OCV_CAPSULE, hv_I_CAPSULE, hv_Row_train_ocv_CAPSULE;
	HTuple  hv_Column_train_ocv_CAPSULE, hv_Angle_train_ocv_CAPSULE;
	HTuple  hv_Score_train_ocv_CAPSULE, hv_HomMat2D_train_ocv_CAPSULE;
	HTuple  hv_Row_ocv_CAPSULE, hv_Column_ocv_CAPSULE, hv_Angle_ocv_CAPSULE;
	HTuple  hv_Score_ocv_CAPSULE, hv_HomMat2D_OCV_CAPSULE, hv_NumError_ocv_CAPSULE;

	//jiance 
	HObject  ho_Region, ho_SelectedRegions;
	HTuple   hv_ERROR_ROW, hv_ERROR_COLUMN;

	// Procedure declarations 
	// Chapter: Graphics / Text
	// Short Description: Set font independent of OS 
	NON_RETURN set_display_font(HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold,
		HTuple hv_Slant);
	// Chapter: Graphics / Text
	// Short Description: This procedure displays 'Click 'Run' to continue' in the lower right corner of the screen. 
	NON_RETURN disp_continue_message(HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box);
	// Chapter: Graphics / Text
	// Short Description: This procedure writes a text message. 
	NON_RETURN disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
		HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
	// Local procedures 
	NON_RETURN dev_display_profile_line(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1,
		HTuple hv_Length2);
	NON_RETURN dev_display_measure_object(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1,
		HTuple hv_Length2);
	NON_RETURN dev_display_profile_points(HTuple hv_PRows, HTuple hv_PCols, HTuple hv_Row,
		HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1, HTuple hv_Length2);
	// Short Description: Displays text right of the center of two given points. 
	NON_RETURN p_disp_text_right_of_center(HTuple hv_WindowHandle, HTuple hv_Text, HTuple hv_RowFirst,
		HTuple hv_ColFirst, HTuple hv_RowSecond, HTuple hv_ColSecond, HTuple hv_Phi,
		HTuple hv_Distance);
	// Short Description: Displays a marker, which indicates the position of an edge 
	NON_RETURN p_disp_edge_marker(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length,
		HTuple hv_Color, HTuple hv_LineWidth, HTuple hv_WindowHandle);
	// Short Description: Displays text right of the center of two given points. 
	NON_RETURN p_disp_text_left_of_center(HTuple hv_WindowHandle, HTuple hv_Text, HTuple hv_RowFirst,
		HTuple hv_ColFirst, HTuple hv_RowSecond, HTuple hv_ColSecond, HTuple hv_Phi,
		HTuple hv_Distance);
	// Short Description: Displays the dimension of the measured edge pairs. 
	NON_RETURN p_disp_dimensions(HTuple hv_RowEdgeFirst, HTuple hv_ColumnEdgeFirst, HTuple hv_RowEdgeSecond,
		HTuple hv_ColumnEdgeSecond, HTuple hv_IntraDistance, HTuple hv_InterDistance,
		HTuple hv_Phi, HTuple hv_Length, HTuple hv_WindowHandle);
	NON_RETURN get_tmp_dir(HTuple *hv_LocalTemp);
	NON_RETURN gen_initial_trainfile(HTuple hv_TrainFileName);

	NON_RETURN INIT_CAMERA_WINDOW(Hlong lWWindowID);
	NON_RETURN INIT_OCR_CLASS_SVM(void);
	NON_RETURN ACTION_NCC_MODEL(void);
	NON_RETURN ACTION_FIND_OBJECT_YES_OR_NO(void);
	NON_RETURN ACTION_CONFIRM_OBJECT(void);
	NON_RETURN INIT_LOCATION_CHAR_AND_LOGO(void);
	NON_RETURN INIT_LOCATION_PIN(void);
	NON_RETURN INIT_FONT_PIN(void);
	NON_RETURN ACTION_MEASURE_PIN(void);
	NON_RETURN ACTION_BACKUP_DATA_PIN(void);
	NON_RETURN ACTION_CALCULATE_RESULT_OF_PIN(void);
	NON_RETURN DISPLAY_RESULT_OF_ALL(void);
	NON_RETURN CLOSE_MEASURE_PIN(void);

	NON_RETURN GET_CROP_IMAGE_ACTION(void);
	NON_RETURN OCR_CORE_PRE_PROCESSING(void);
	NON_RETURN OCR_ORDER_SELECTED_REGION(void);
	NON_RETURN OCR_DO_OCR_CLASS_SVM(void);
	NON_RETURN DISPLAY_OCR_RESULT(void);

	//ocv
	NON_RETURN INIT_TRAIN_OCV_ACTION(void);
	NON_RETURN ACTION_TRAIN_OCV_VARMODEL(void);
	NON_RETURN ACTION_OCV_CORE(void);
	NON_RETURN CLEAR_OCV_MODELDATA(void);
	NON_RETURN INIT_TRAIN_OCV_ACTION_CAPSULE(void);
	NON_RETURN ACTION_TRAIN_OCV_VARMODEL_CAPSULE(void);
	NON_RETURN ACTION_OCV_CORE_CAPSULE(void);
	NON_RETURN CLEAR_OCV_MODELDATA_CAPSULE(void);


	//检测的
	NON_RETURN ACTION_DETECTION_ALL_OF_FLAW(void);
	NON_RETURN ACTION_DETECTION_00_CAPSULE(void);
	NON_RETURN ACTION_DETECTION_01_CAPSULE(void);
	NON_RETURN ACTION_DETECTION_02_CAPSULE(void);
	NON_RETURN ACTION_DETECTION_03_CAPSULE(void);
	NON_RETURN ACTION_DETECTION_04_CAPSULE(void);
	NON_RETURN ACTION_DETECTION_10_MARK(void);
	NON_RETURN ACTION_DETECTION_11_MARK(void);
	NON_RETURN ACTION_DETECTION_12_MARK(void);
	NON_RETURN ACTION_DETECTION_13_MARK(void);
	NON_RETURN ACTION_DETECTION_14_MARK(void);
	NON_RETURN ACTION_DETECTION_15_MARK(void);
	NON_RETURN ACTION_DETECTION_16_MARK(void);
	NON_RETURN ACTION_DETECTION_17_MARK(void);
	NON_RETURN ACTION_DETECTION_18_MARK(void);
	NON_RETURN ACTION_DETECTION_19_MARK(void);
	NON_RETURN ACTION_DETECTION_20_PIN(void);
	NON_RETURN ACTION_DETECTION_21_PIN(void);
	NON_RETURN ACTION_DETECTION_22_PIN(void);
	NON_RETURN ACTION_DETECTION_23_PIN(void);
	NON_RETURN ACTION_DETECTION_24_PIN(void);
	NON_RETURN ACTION_DETECTION_25_PIN(void);
	NON_RETURN ACTION_DETECTION_26_PIN(void);
	NON_RETURN ACTION_DETECTION_27_PIN(void);
	NON_RETURN ACTION_DETECTION_28_PIN(void);
	NON_RETURN ACTION_DETECTION_29_PIN(void);


};
