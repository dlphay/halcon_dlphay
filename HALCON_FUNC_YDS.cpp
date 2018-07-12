

#include "stdafx.h"
#include "HALCON_FUNC_YDS.H"

#define RATIO_PIXAL_TO_UM   7.8154
#define     ROW_TOP                  45.5;
#define     ROW_BOTTON               460.5;
#define     ROW_TOP_INSIDE           75.5;
#define     ROW_BOTTON_INSIDE        430.5;
#define     COLUMN_LEFT              37.5;
#define     COLUMN_RIGHT             567.5;
#define     COLUMN_LEFT_INSIDE       67.5;
#define     COLUMN_RIGHT_INSIDE      537.5;
typedef void NON_RETURN;

NON_RETURN HALCON_FUNC_YDS::set_display_font(HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold,
	HTuple hv_Slant)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_OS, hv_BufferWindowHandle, hv_Ascent;
	HTuple  hv_Descent, hv_Width, hv_Height, hv_Scale, hv_Exception;
	HTuple  hv_SubFamily, hv_Fonts, hv_SystemFonts, hv_Guess;
	HTuple  hv_I, hv_Index, hv_AllowedFontSizes, hv_Distances;
	HTuple  hv_Indices, hv_FontSelRegexp, hv_FontsCourier;

	//This procedure sets the text font of the current window with
	//the specified attributes.
	//It is assumed that following fonts are installed on the system:
	//Windows: Courier New, Arial Times New Roman
	//Mac OS X: CourierNewPS, Arial, TimesNewRomanPS
	//Linux: courier, helvetica, times
	//Because fonts are displayed smaller on Linux than on Windows,
	//a scaling factor of 1.25 is used the get comparable results.
	//For Linux, only a limited number of font sizes is supported,
	//to get comparable results, it is recommended to use one of the
	//following sizes: 9, 11, 14, 16, 20, 27
	//(which will be mapped internally on Linux systems to 11, 14, 17, 20, 25, 34)
	//
	//Input parameters:
	//WindowHandle: The graphics window for which the font will be set
	//Size: The font size. If Size=-1, the default of 16 is used.
	//Bold: If set to 'true', a bold font is used
	//Slant: If set to 'true', a slanted font is used
	//
	GetSystem("operating_system", &hv_OS);
	// dev_get_preferences(...); only in hdevelop
	// dev_set_preferences(...); only in hdevelop
	if (0 != (HTuple(hv_Size == HTuple()).TupleOr(hv_Size == -1)))
	{
		hv_Size = 16;
	}
	if (0 != ((hv_OS.TupleSubstr(0, 2)) == HTuple("Win")))
	{
		//Set font on Windows systems
		try
		{
			//Check, if font scaling is switched on
			OpenWindow(0, 0, 256, 256, 0, "buffer", "", &hv_BufferWindowHandle);
			SetFont(hv_BufferWindowHandle, "-Consolas-16-*-0-*-*-1-");
			GetStringExtents(hv_BufferWindowHandle, "test_string", &hv_Ascent, &hv_Descent,
				&hv_Width, &hv_Height);
			//Expected width is 110
			hv_Scale = 110.0 / hv_Width;
			hv_Size = (hv_Size*hv_Scale).TupleInt();
			CloseWindow(hv_BufferWindowHandle);
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			//throw (Exception)
		}
		if (0 != (HTuple(hv_Font == HTuple("Courier")).TupleOr(hv_Font == HTuple("courier"))))
		{
			hv_Font = "Courier New";
		}
		else if (0 != (hv_Font == HTuple("mono")))
		{
			hv_Font = "Consolas";
		}
		else if (0 != (hv_Font == HTuple("sans")))
		{
			hv_Font = "Arial";
		}
		else if (0 != (hv_Font == HTuple("serif")))
		{
			hv_Font = "Times New Roman";
		}
		if (0 != (hv_Bold == HTuple("true")))
		{
			hv_Bold = 1;
		}
		else if (0 != (hv_Bold == HTuple("false")))
		{
			hv_Bold = 0;
		}
		else
		{
			hv_Exception = "Wrong value of control parameter Bold";
			throw HalconCpp::HException(hv_Exception);
		}
		if (0 != (hv_Slant == HTuple("true")))
		{
			hv_Slant = 1;
		}
		else if (0 != (hv_Slant == HTuple("false")))
		{
			hv_Slant = 0;
		}
		else
		{
			hv_Exception = "Wrong value of control parameter Slant";
			throw HalconCpp::HException(hv_Exception);
		}
		try
		{
			SetFont(hv_WindowHandle, ((((((("-" + hv_Font) + "-") + hv_Size) + "-*-") + hv_Slant) + "-*-*-") + hv_Bold) + "-");
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			//throw (Exception)
		}
	}
	else if (0 != ((hv_OS.TupleSubstr(0, 2)) == HTuple("Dar")))
	{
		//Set font on Mac OS X systems. Since OS X does not have a strict naming
		//scheme for font attributes, we use tables to determine the correct font
		//name.
		hv_SubFamily = 0;
		if (0 != (hv_Slant == HTuple("true")))
		{
			hv_SubFamily = hv_SubFamily | 1;
		}
		else if (0 != (hv_Slant != HTuple("false")))
		{
			hv_Exception = "Wrong value of control parameter Slant";
			throw HalconCpp::HException(hv_Exception);
		}
		if (0 != (hv_Bold == HTuple("true")))
		{
			hv_SubFamily = hv_SubFamily | 2;
		}
		else if (0 != (hv_Bold != HTuple("false")))
		{
			hv_Exception = "Wrong value of control parameter Bold";
			throw HalconCpp::HException(hv_Exception);
		}
		if (0 != (hv_Font == HTuple("mono")))
		{
			hv_Fonts.Clear();
			hv_Fonts[0] = "Menlo-Regular";
			hv_Fonts[1] = "Menlo-Italic";
			hv_Fonts[2] = "Menlo-Bold";
			hv_Fonts[3] = "Menlo-BoldItalic";
		}
		else if (0 != (HTuple(hv_Font == HTuple("Courier")).TupleOr(hv_Font == HTuple("courier"))))
		{
			hv_Fonts.Clear();
			hv_Fonts[0] = "CourierNewPSMT";
			hv_Fonts[1] = "CourierNewPS-ItalicMT";
			hv_Fonts[2] = "CourierNewPS-BoldMT";
			hv_Fonts[3] = "CourierNewPS-BoldItalicMT";
		}
		else if (0 != (hv_Font == HTuple("sans")))
		{
			hv_Fonts.Clear();
			hv_Fonts[0] = "ArialMT";
			hv_Fonts[1] = "Arial-ItalicMT";
			hv_Fonts[2] = "Arial-BoldMT";
			hv_Fonts[3] = "Arial-BoldItalicMT";
		}
		else if (0 != (hv_Font == HTuple("serif")))
		{
			hv_Fonts.Clear();
			hv_Fonts[0] = "TimesNewRomanPSMT";
			hv_Fonts[1] = "TimesNewRomanPS-ItalicMT";
			hv_Fonts[2] = "TimesNewRomanPS-BoldMT";
			hv_Fonts[3] = "TimesNewRomanPS-BoldItalicMT";
		}
		else
		{
			//Attempt to figure out which of the fonts installed on the system
			//the user could have meant.
			QueryFont(hv_WindowHandle, &hv_SystemFonts);
			hv_Fonts.Clear();
			hv_Fonts.Append(hv_Font);
			hv_Fonts.Append(hv_Font);
			hv_Fonts.Append(hv_Font);
			hv_Fonts.Append(hv_Font);
			hv_Guess.Clear();
			hv_Guess.Append(hv_Font);
			hv_Guess.Append(hv_Font + "-Regular");
			hv_Guess.Append(hv_Font + "MT");
			{
				HTuple end_val100 = (hv_Guess.TupleLength()) - 1;
				HTuple step_val100 = 1;
				for (hv_I = 0; hv_I.Continue(end_val100, step_val100); hv_I += step_val100)
				{
					TupleFind(hv_SystemFonts, HTuple(hv_Guess[hv_I]), &hv_Index);
					if (0 != (hv_Index != -1))
					{
						hv_Fonts[0] = HTuple(hv_Guess[hv_I]);
						break;
					}
				}
			}
			//Guess name of slanted font
			hv_Guess.Clear();
			hv_Guess.Append(hv_Font + "-Italic");
			hv_Guess.Append(hv_Font + "-ItalicMT");
			hv_Guess.Append(hv_Font + "-Oblique");
			{
				HTuple end_val109 = (hv_Guess.TupleLength()) - 1;
				HTuple step_val109 = 1;
				for (hv_I = 0; hv_I.Continue(end_val109, step_val109); hv_I += step_val109)
				{
					TupleFind(hv_SystemFonts, HTuple(hv_Guess[hv_I]), &hv_Index);
					if (0 != (hv_Index != -1))
					{
						hv_Fonts[1] = HTuple(hv_Guess[hv_I]);
						break;
					}
				}
			}
			//Guess name of bold font
			hv_Guess.Clear();
			hv_Guess.Append(hv_Font + "-Bold");
			hv_Guess.Append(hv_Font + "-BoldMT");
			{
				HTuple end_val118 = (hv_Guess.TupleLength()) - 1;
				HTuple step_val118 = 1;
				for (hv_I = 0; hv_I.Continue(end_val118, step_val118); hv_I += step_val118)
				{
					TupleFind(hv_SystemFonts, HTuple(hv_Guess[hv_I]), &hv_Index);
					if (0 != (hv_Index != -1))
					{
						hv_Fonts[2] = HTuple(hv_Guess[hv_I]);
						break;
					}
				}
			}
			//Guess name of bold slanted font
			hv_Guess.Clear();
			hv_Guess.Append(hv_Font + "-BoldItalic");
			hv_Guess.Append(hv_Font + "-BoldItalicMT");
			hv_Guess.Append(hv_Font + "-BoldOblique");
			{
				HTuple end_val127 = (hv_Guess.TupleLength()) - 1;
				HTuple step_val127 = 1;
				for (hv_I = 0; hv_I.Continue(end_val127, step_val127); hv_I += step_val127)
				{
					TupleFind(hv_SystemFonts, HTuple(hv_Guess[hv_I]), &hv_Index);
					if (0 != (hv_Index != -1))
					{
						hv_Fonts[3] = HTuple(hv_Guess[hv_I]);
						break;
					}
				}
			}
		}
		hv_Font = ((const HTuple&)hv_Fonts)[hv_SubFamily];
		try
		{
			SetFont(hv_WindowHandle, (hv_Font + "-") + hv_Size);
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			//throw (Exception)
		}
	}
	else
	{
		//Set font for UNIX systems
		hv_Size = hv_Size*1.25;
		hv_AllowedFontSizes.Clear();
		hv_AllowedFontSizes[0] = 11;
		hv_AllowedFontSizes[1] = 14;
		hv_AllowedFontSizes[2] = 17;
		hv_AllowedFontSizes[3] = 20;
		hv_AllowedFontSizes[4] = 25;
		hv_AllowedFontSizes[5] = 34;
		if (0 != ((hv_AllowedFontSizes.TupleFind(hv_Size)) == -1))
		{
			hv_Distances = (hv_AllowedFontSizes - hv_Size).TupleAbs();
			TupleSortIndex(hv_Distances, &hv_Indices);
			hv_Size = ((const HTuple&)hv_AllowedFontSizes)[HTuple(hv_Indices[0])];
		}
		if (0 != (HTuple(hv_Font == HTuple("mono")).TupleOr(hv_Font == HTuple("Courier"))))
		{
			hv_Font = "courier";
		}
		else if (0 != (hv_Font == HTuple("sans")))
		{
			hv_Font = "helvetica";
		}
		else if (0 != (hv_Font == HTuple("serif")))
		{
			hv_Font = "times";
		}
		if (0 != (hv_Bold == HTuple("true")))
		{
			hv_Bold = "bold";
		}
		else if (0 != (hv_Bold == HTuple("false")))
		{
			hv_Bold = "medium";
		}
		else
		{
			hv_Exception = "Wrong value of control parameter Bold";
			throw HalconCpp::HException(hv_Exception);
		}
		if (0 != (hv_Slant == HTuple("true")))
		{
			if (0 != (hv_Font == HTuple("times")))
			{
				hv_Slant = "i";
			}
			else
			{
				hv_Slant = "o";
			}
		}
		else if (0 != (hv_Slant == HTuple("false")))
		{
			hv_Slant = "r";
		}
		else
		{
			hv_Exception = "Wrong value of control parameter Slant";
			throw HalconCpp::HException(hv_Exception);
		}
		try
		{
			SetFont(hv_WindowHandle, ((((((("-adobe-" + hv_Font) + "-") + hv_Bold) + "-") + hv_Slant) + "-normal-*-") + hv_Size) + "-*-*-*-*-*-*-*");
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			if (0 != (HTuple((hv_OS.TupleSubstr(0, 4)) == HTuple("Linux")).TupleAnd(hv_Font == HTuple("courier"))))
			{
				QueryFont(hv_WindowHandle, &hv_Fonts);
				hv_FontSelRegexp = (("^-[^-]*-[^-]*[Cc]ourier[^-]*-" + hv_Bold) + "-") + hv_Slant;
				hv_FontsCourier = (hv_Fonts.TupleRegexpSelect(hv_FontSelRegexp)).TupleRegexpMatch(hv_FontSelRegexp);
				if (0 != ((hv_FontsCourier.TupleLength()) == 0))
				{
					hv_Exception = "Wrong font name";
					//throw (Exception)
				}
				else
				{
					try
					{
						SetFont(hv_WindowHandle, ((HTuple(hv_FontsCourier[0]) + "-normal-*-") + hv_Size) + "-*-*-*-*-*-*-*");
					}
					// catch (Exception) 
					catch (HalconCpp::HException &HDevExpDefaultException)
					{
						HDevExpDefaultException.ToHTuple(&hv_Exception);
						//throw (Exception)
					}
				}
			}
			//throw (Exception)
		}
	}
	// dev_set_preferences(...); only in hdevelop
	return;
}
NON_RETURN HALCON_FUNC_YDS::disp_continue_message(HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_ContinueMessage, hv_Row, hv_Column;
	HTuple  hv_Width, hv_Height, hv_Ascent, hv_Descent, hv_TextWidth;
	HTuple  hv_TextHeight;

	//This procedure displays 'Press Run (F5) to continue' in the
	//lower right corner of the screen.
	//It uses the procedure disp_message.
	//
	//Input parameters:
	//WindowHandle: The window, where the text shall be displayed
	//Color: defines the text color.
	//   If set to '' or 'auto', the currently set color is used.
	//Box: If set to 'true', the text is displayed in a box.
	//
	hv_ContinueMessage = "Press Run (F5) to continue";
	GetWindowExtents(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Width, &hv_Height);
	GetStringExtents(hv_WindowHandle, (" " + hv_ContinueMessage) + " ", &hv_Ascent, &hv_Descent,
		&hv_TextWidth, &hv_TextHeight);
	disp_message(hv_WindowHandle, hv_ContinueMessage, "window", (hv_Height - hv_TextHeight) - 12,
		(hv_Width - hv_TextWidth) - 12, hv_Color, hv_Box);
	return;
}
NON_RETURN HALCON_FUNC_YDS::disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Red, hv_Green, hv_Blue, hv_Row1Part;
	HTuple  hv_Column1Part, hv_Row2Part, hv_Column2Part, hv_RowWin;
	HTuple  hv_ColumnWin, hv_WidthWin, hv_HeightWin, hv_MaxAscent;
	HTuple  hv_MaxDescent, hv_MaxWidth, hv_MaxHeight, hv_R1;
	HTuple  hv_C1, hv_FactorRow, hv_FactorColumn, hv_UseShadow;
	HTuple  hv_ShadowColor, hv_Exception, hv_Width, hv_Index;
	HTuple  hv_Ascent, hv_Descent, hv_W, hv_H, hv_FrameHeight;
	HTuple  hv_FrameWidth, hv_R2, hv_C2, hv_DrawMode, hv_CurrentColor;

	//This procedure displays text in a graphics window.
	//
	//Input parameters:
	//WindowHandle: The WindowHandle of the graphics window, where
	//   the message should be displayed
	//String: A tuple of strings containing the text message to be displayed
	//CoordSystem: If set to 'window', the text position is given
	//   with respect to the window coordinate system.
	//   If set to 'image', image coordinates are used.
	//   (This may be useful in zoomed images.)
	//Row: The row coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Column: The column coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Color: defines the color of the text as string.
	//   If set to [], '' or 'auto' the currently set color is used.
	//   If a tuple of strings is passed, the colors are used cyclically
	//   for each new textline.
	//Box: If Box[0] is set to 'true', the text is written within an orange box.
	//     If set to' false', no box is displayed.
	//     If set to a color string (e.g. 'white', '#FF00CC', etc.),
	//       the text is written in a box of that color.
	//     An optional second value for Box (Box[1]) controls if a shadow is displayed:
	//       'true' -> display a shadow in a default color
	//       'false' -> display no shadow (same as if no second value is given)
	//       otherwise -> use given string as color string for the shadow color
	//
	//Prepare window
	GetRgb(hv_WindowHandle, &hv_Red, &hv_Green, &hv_Blue);
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	SetPart(hv_WindowHandle, 0, 0, hv_HeightWin - 1, hv_WidthWin - 1);
	//
	//default settings
	if (0 != (hv_Row == -1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column == -1))
	{
		hv_Column = 12;
	}
	if (0 != (hv_Color == HTuple()))
	{
		hv_Color = "";
	}
	//
	hv_String = (("" + hv_String) + "").TupleSplit("\n");
	//
	//Estimate extentions of text depending on font size.
	GetFontExtents(hv_WindowHandle, &hv_MaxAscent, &hv_MaxDescent, &hv_MaxWidth, &hv_MaxHeight);
	if (0 != (hv_CoordSystem == HTuple("window")))
	{
		hv_R1 = hv_Row;
		hv_C1 = hv_Column;
	}
	else
	{
		//Transform image to window coordinates
		hv_FactorRow = (1.*hv_HeightWin) / ((hv_Row2Part - hv_Row1Part) + 1);
		hv_FactorColumn = (1.*hv_WidthWin) / ((hv_Column2Part - hv_Column1Part) + 1);
		hv_R1 = ((hv_Row - hv_Row1Part) + 0.5)*hv_FactorRow;
		hv_C1 = ((hv_Column - hv_Column1Part) + 0.5)*hv_FactorColumn;
	}
	//
	//Display text box depending on text size
	hv_UseShadow = 1;
	hv_ShadowColor = "gray";
	if (0 != (HTuple(hv_Box[0]) == HTuple("true")))
	{
		hv_Box[0] = "#fce9d4";
		hv_ShadowColor = "#f28d26";
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1]) == HTuple("true")))
		{
			//Use default ShadowColor set above
		}
		else if (0 != (HTuple(hv_Box[1]) == HTuple("false")))
		{
			hv_UseShadow = 0;
		}
		else
		{
			hv_ShadowColor = ((const HTuple&)hv_Box)[1];
			//Valid color?
			try
			{
				SetColor(hv_WindowHandle, HTuple(hv_Box[1]));
			}
			// catch (Exception) 
			catch (HalconCpp::HException &HDevExpDefaultException)
			{
				HDevExpDefaultException.ToHTuple(&hv_Exception);
				hv_Exception = "Wrong value of control parameter Box[1] (must be a 'true', 'false', or a valid color string)";
				throw HalconCpp::HException(hv_Exception);
			}
		}
	}
	if (0 != (HTuple(hv_Box[0]) != HTuple("false")))
	{
		//Valid color?
		try
		{
			SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			hv_Exception = "Wrong value of control parameter Box[0] (must be a 'true', 'false', or a valid color string)";
			throw HalconCpp::HException(hv_Exception);
		}
		//Calculate box extents
		hv_String = (" " + hv_String) + " ";
		hv_Width = HTuple();
		{
			HTuple end_val93 = (hv_String.TupleLength()) - 1;
			HTuple step_val93 = 1;
			for (hv_Index = 0; hv_Index.Continue(end_val93, step_val93); hv_Index += step_val93)
			{
				GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent,
					&hv_Descent, &hv_W, &hv_H);
				hv_Width = hv_Width.TupleConcat(hv_W);
			}
		}
		hv_FrameHeight = hv_MaxHeight*(hv_String.TupleLength());
		hv_FrameWidth = (HTuple(0).TupleConcat(hv_Width)).TupleMax();
		hv_R2 = hv_R1 + hv_FrameHeight;
		hv_C2 = hv_C1 + hv_FrameWidth;
		//Display rectangles
		GetDraw(hv_WindowHandle, &hv_DrawMode);
		SetDraw(hv_WindowHandle, "fill");
		//Set shadow color
		SetColor(hv_WindowHandle, hv_ShadowColor);
		if (0 != hv_UseShadow)
		{
			DispRectangle1(hv_WindowHandle, hv_R1 + 1, hv_C1 + 1, hv_R2 + 1, hv_C2 + 1);
		}
		//Set box color
		SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		DispRectangle1(hv_WindowHandle, hv_R1, hv_C1, hv_R2, hv_C2);
		SetDraw(hv_WindowHandle, hv_DrawMode);
	}
	//Write text.
	{
		HTuple end_val115 = (hv_String.TupleLength()) - 1;
		HTuple step_val115 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val115, step_val115); hv_Index += step_val115)
		{
			hv_CurrentColor = ((const HTuple&)hv_Color)[hv_Index % (hv_Color.TupleLength())];
			if (0 != (HTuple(hv_CurrentColor != HTuple("")).TupleAnd(hv_CurrentColor != HTuple("auto"))))
			{
				SetColor(hv_WindowHandle, hv_CurrentColor);
			}
			else
			{
				SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
			}
			hv_Row = hv_R1 + (hv_MaxHeight*hv_Index);
			SetTposition(hv_WindowHandle, hv_Row, hv_C1);
			WriteString(hv_WindowHandle, HTuple(hv_String[hv_Index]));
		}
	}
	//Reset changed window settings
	SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
	SetPart(hv_WindowHandle, hv_Row1Part, hv_Column1Part, hv_Row2Part, hv_Column2Part);
	return;
}
NON_RETURN HALCON_FUNC_YDS::dev_display_profile_line(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1,
	HTuple hv_Length2)
{

	// Local iconic variables
	HObject  ho_CProfile, ho_CArrow, ho_CMidPoint;

	// Local control variables
	HTuple  hv_ArrowAngle, hv_ArrowLength, hv_PSize;
	HTuple  hv_RowStart, hv_RowEnd, hv_ColStart, hv_ColEnd;

	hv_ArrowAngle = (HTuple(45).TupleRad()) / 2;
	hv_ArrowLength = hv_Length1*0.2;
	hv_PSize = hv_Length2*0.2;
	hv_RowStart = hv_Row + ((hv_Phi.TupleSin())*hv_Length1);
	hv_RowEnd = hv_Row - ((hv_Phi.TupleSin())*hv_Length1);
	hv_ColStart = hv_Col - ((hv_Phi.TupleCos())*hv_Length1);
	hv_ColEnd = hv_Col + ((hv_Phi.TupleCos())*hv_Length1);
	GenContourPolygonXld(&ho_CProfile, hv_RowStart.TupleConcat(hv_RowEnd), hv_ColStart.TupleConcat(hv_ColEnd));
	GenContourPolygonXld(&ho_CArrow, ((hv_RowEnd - (((hv_ArrowAngle - hv_Phi).TupleSin())*hv_ArrowLength)).TupleConcat(hv_RowEnd)).TupleConcat(hv_RowEnd + (((hv_ArrowAngle + hv_Phi).TupleSin())*hv_ArrowLength)),
		((hv_ColEnd - (((hv_ArrowAngle - hv_Phi).TupleCos())*hv_ArrowLength)).TupleConcat(hv_ColEnd)).TupleConcat(hv_ColEnd - (((hv_ArrowAngle + hv_Phi).TupleCos())*hv_ArrowLength)));
	GenContourPolygonXld(&ho_CMidPoint, (hv_Row - ((((HTuple(90).TupleRad()) + hv_Phi).TupleSin())*hv_PSize)).TupleConcat(hv_Row - (((hv_Phi - (HTuple(90).TupleRad())).TupleSin())*hv_PSize)),
		(hv_Col + ((((HTuple(90).TupleRad()) + hv_Phi).TupleCos())*hv_PSize)).TupleConcat(hv_Col + (((hv_Phi - (HTuple(90).TupleRad())).TupleCos())*hv_PSize)));
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), 4);
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "white");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_CProfile, HDevWindowStack::GetActive());
	if (HDevWindowStack::IsOpen())
		DispObj(ho_CArrow, HDevWindowStack::GetActive());
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), 2);
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "black");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_CProfile, HDevWindowStack::GetActive());
	if (HDevWindowStack::IsOpen())
		DispObj(ho_CArrow, HDevWindowStack::GetActive());
	return;
}
NON_RETURN HALCON_FUNC_YDS::dev_display_measure_object(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1,
	HTuple hv_Length2)
{

	// Local iconic variables
	HObject  ho_Contour;

	// Local control variables
	HTuple  hv_RowStart, hv_RowEnd, hv_ColStart, hv_ColEnd;
	HTuple  hv_drow, hv_dcol;

	hv_RowStart = hv_Row + ((hv_Phi.TupleSin())*hv_Length1);
	hv_RowEnd = hv_Row - ((hv_Phi.TupleSin())*hv_Length1);
	hv_ColStart = hv_Col - ((hv_Phi.TupleCos())*hv_Length1);
	hv_ColEnd = hv_Col + ((hv_Phi.TupleCos())*hv_Length1);
	hv_drow = (((HTuple(90).TupleRad()) - hv_Phi).TupleSin())*hv_Length2;
	hv_dcol = (((HTuple(90).TupleRad()) - hv_Phi).TupleCos())*hv_Length2;
	GenContourPolygonXld(&ho_Contour, ((((hv_RowStart - hv_drow).TupleConcat(hv_RowEnd - hv_drow)).TupleConcat(hv_RowEnd + hv_drow)).TupleConcat(hv_RowStart + hv_drow)).TupleConcat(hv_RowStart - hv_drow),
		((((hv_ColStart - hv_dcol).TupleConcat(hv_ColEnd - hv_dcol)).TupleConcat(hv_ColEnd + hv_dcol)).TupleConcat(hv_ColStart + hv_dcol)).TupleConcat(hv_ColStart - hv_dcol));
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), 2);
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "green");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Contour, HDevWindowStack::GetActive());
	dev_display_profile_line(hv_Row, hv_Col, hv_Phi, hv_Length1, hv_Length2);
	return;
}
NON_RETURN HALCON_FUNC_YDS::dev_display_profile_points(HTuple hv_PRows, HTuple hv_PCols, HTuple hv_Row,
	HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length1, HTuple hv_Length2)
{

	// Local iconic variables
	HObject  ho_CPoint;

	// Local control variables
	HTuple  hv_PSize, hv_RowStart, hv_RowEnd, hv_ColStart;
	HTuple  hv_ColEnd, hv_idx;

	hv_PSize = hv_Length2*0.5;
	hv_RowStart = hv_Row + ((hv_Phi.TupleSin())*hv_Length1);
	hv_RowEnd = hv_Row - ((hv_Phi.TupleSin())*hv_Length1);
	hv_ColStart = hv_Col - ((hv_Phi.TupleCos())*hv_Length1);
	hv_ColEnd = hv_Col + ((hv_Phi.TupleCos())*hv_Length1);
	{
		HTuple end_val5 = (hv_PRows.TupleLength()) - 1;
		HTuple step_val5 = 1;
		for (hv_idx = 0; hv_idx.Continue(end_val5, step_val5); hv_idx += step_val5)
		{
			GenContourPolygonXld(&ho_CPoint, (HTuple(hv_PRows[hv_idx]) - ((((HTuple(90).TupleRad()) + hv_Phi).TupleSin())*hv_PSize)).TupleConcat(HTuple(hv_PRows[hv_idx]) - (((hv_Phi - (HTuple(90).TupleRad())).TupleSin())*hv_PSize)),
				(HTuple(hv_PCols[hv_idx]) + ((((HTuple(90).TupleRad()) + hv_Phi).TupleCos())*hv_PSize)).TupleConcat(HTuple(hv_PCols[hv_idx]) + (((hv_Phi - (HTuple(90).TupleRad())).TupleCos())*hv_PSize)));
			if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(), "red");
			if (HDevWindowStack::IsOpen())
				SetLineWidth(HDevWindowStack::GetActive(), 3);
			if (HDevWindowStack::IsOpen())
				DispObj(ho_CPoint, HDevWindowStack::GetActive());
		}
	}
	return;
}
NON_RETURN HALCON_FUNC_YDS::p_disp_text_right_of_center(HTuple hv_WindowHandle, HTuple hv_Text, HTuple hv_RowFirst,
	HTuple hv_ColFirst, HTuple hv_RowSecond, HTuple hv_ColSecond, HTuple hv_Phi,
	HTuple hv_Distance)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Row1Part, hv_Column1Part, hv_Row2Part;
	HTuple  hv_Column2Part, hv_RowWin, hv_ColumnWin, hv_WidthWin;
	HTuple  hv_HeightWin, hv_FactorRow, hv_FactorColumn, hv_Ascent;
	HTuple  hv_Descent, hv_Width, hv_Height, hv_RowCenter, hv_ColCenter;
	HTuple  hv_RowPos, hv_ColPos, hv_RowText, hv_ColText;

	//Determine factors for the adaptation of the string extents that might be necessary
	//because of image zooming.
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	hv_FactorRow = (1.*((hv_Row2Part - hv_Row1Part) + 1)) / hv_HeightWin;
	hv_FactorColumn = (1.*((hv_Column2Part - hv_Column1Part) + 1)) / hv_WidthWin;
	//
	//Determine the extent of the string and its position.
	GetStringExtents(hv_WindowHandle, hv_Text, &hv_Ascent, &hv_Descent, &hv_Width,
		&hv_Height);
	hv_Width = hv_Width*hv_FactorColumn;
	hv_Height = hv_Height*hv_FactorRow;
	hv_RowCenter = (hv_RowFirst + hv_RowSecond) / 2.0;
	hv_ColCenter = (hv_ColFirst + hv_ColSecond) / 2.0;
	if (0 != ((hv_Phi.TupleSin())<0))
	{
		hv_Distance = -hv_Distance;
	}
	hv_RowPos = hv_RowCenter + (hv_Distance*(hv_Phi.TupleCos()));
	hv_ColPos = hv_ColCenter + (hv_Distance*(hv_Phi.TupleSin()));
	hv_RowText = hv_RowPos - (hv_Height / 2.0);
	hv_ColText = hv_ColPos;
	//
	//Set the text position and color and display the text.
	SetTposition(hv_WindowHandle, hv_RowText, hv_ColText);
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "black");
	WriteString(hv_WindowHandle, hv_Text);
	return;
}
NON_RETURN HALCON_FUNC_YDS::p_disp_edge_marker(HTuple hv_Row, HTuple hv_Col, HTuple hv_Phi, HTuple hv_Length,
	HTuple hv_Color, HTuple hv_LineWidth, HTuple hv_WindowHandle)
{

	// Local iconic variables
	HObject  ho_Marker;

	// Local control variables
	HTuple  hv_RowStart, hv_RowEnd, hv_ColStart, hv_ColEnd;

	//Determine start and end point of the edge marker.
	hv_RowStart = hv_Row + (hv_Length*(hv_Phi.TupleCos()));
	hv_RowEnd = hv_Row - (hv_Length*(hv_Phi.TupleCos()));
	hv_ColStart = hv_Col + (hv_Length*(hv_Phi.TupleSin()));
	hv_ColEnd = hv_Col - (hv_Length*(hv_Phi.TupleSin()));
	//
	//Generate a contour that connects the start and end point.
	GenContourPolygonXld(&ho_Marker, hv_RowStart.TupleConcat(hv_RowEnd), hv_ColStart.TupleConcat(hv_ColEnd));
	//
	//Display the contour with  the specified style.
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), hv_Color);
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), hv_LineWidth);
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Marker, HDevWindowStack::GetActive());
	//
	//Reset the line width.
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), 1);
	return;
}
NON_RETURN HALCON_FUNC_YDS::p_disp_text_left_of_center(HTuple hv_WindowHandle, HTuple hv_Text, HTuple hv_RowFirst,
	HTuple hv_ColFirst, HTuple hv_RowSecond, HTuple hv_ColSecond, HTuple hv_Phi,
	HTuple hv_Distance)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Row1Part, hv_Column1Part, hv_Row2Part;
	HTuple  hv_Column2Part, hv_RowWin, hv_ColumnWin, hv_WidthWin;
	HTuple  hv_HeightWin, hv_FactorRow, hv_FactorColumn, hv_Ascent;
	HTuple  hv_Descent, hv_Width, hv_Height, hv_RowCenter, hv_ColCenter;
	HTuple  hv_RowPos, hv_ColPos, hv_RowText, hv_ColText;

	//Determine factors for the adaptation of the string extents that might be necessary
	//because of image zooming.
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	hv_FactorRow = (1.*((hv_Row2Part - hv_Row1Part) + 1)) / hv_HeightWin;
	hv_FactorColumn = (1.*((hv_Column2Part - hv_Column1Part) + 1)) / hv_WidthWin;
	//
	//Determine the extent of the string and its position.
	GetStringExtents(hv_WindowHandle, hv_Text, &hv_Ascent, &hv_Descent, &hv_Width,
		&hv_Height);
	hv_Width = hv_Width*hv_FactorColumn;
	hv_Height = hv_Height*hv_FactorRow;
	hv_RowCenter = (hv_RowFirst + hv_RowSecond) / 2.0;
	hv_ColCenter = (hv_ColFirst + hv_ColSecond) / 2.0;
	if (0 != ((hv_Phi.TupleSin())<0))
	{
		hv_Distance = -hv_Distance;
	}
	hv_RowPos = hv_RowCenter - (hv_Distance*(hv_Phi.TupleCos()));
	hv_ColPos = hv_ColCenter - (hv_Distance*(hv_Phi.TupleSin()));
	hv_RowText = hv_RowPos - (hv_Height / 2.0);
	hv_ColText = hv_ColPos - hv_Width;
	//
	//Set the text position and color and display the text.
	SetTposition(hv_WindowHandle, hv_RowText, hv_ColText);
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "black");
	WriteString(hv_WindowHandle, hv_Text);
	return;
} 
NON_RETURN HALCON_FUNC_YDS::p_disp_dimensions(HTuple hv_RowEdgeFirst, HTuple hv_ColumnEdgeFirst, HTuple hv_RowEdgeSecond,
	HTuple hv_ColumnEdgeSecond, HTuple hv_IntraDistance, HTuple hv_InterDistance,
	HTuple hv_Phi, HTuple hv_Length, HTuple hv_WindowHandle)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Number, hv_i, hv_Text;

	//Loop over all edge pairs.
	hv_Number = hv_RowEdgeFirst.TupleLength();
	{
		HTuple end_val2 = hv_Number - 1;
		HTuple step_val2 = 1;
		for (hv_i = 0; hv_i.Continue(end_val2, step_val2); hv_i += step_val2)
		{
			//
			//Display markers for the edges.
			p_disp_edge_marker(HTuple(hv_RowEdgeFirst[hv_i]), HTuple(hv_ColumnEdgeFirst[hv_i]),
				hv_Phi, hv_Length, "white", 2, hv_WindowHandle);
			p_disp_edge_marker(HTuple(hv_RowEdgeSecond[hv_i]), HTuple(hv_ColumnEdgeSecond[hv_i]),
				hv_Phi, hv_Length, "white", 2, hv_WindowHandle);
			//
			//Display the IntraDistance between the edges.
			hv_Text = ((const HTuple&)hv_IntraDistance)[hv_i];
			p_disp_text_right_of_center(hv_WindowHandle, hv_Text.TupleString(".2f"), HTuple(hv_RowEdgeFirst[hv_i]),
				HTuple(hv_ColumnEdgeFirst[hv_i]), HTuple(hv_RowEdgeSecond[hv_i]), HTuple(hv_ColumnEdgeSecond[hv_i]),
				hv_Phi, 2.0*hv_Length);
		}
	}
	//
	//Loop to display the distance between the edge pairs.
	{
		HTuple end_val14 = hv_Number - 2;
		HTuple step_val14 = 1;
		for (hv_i = 0; hv_i.Continue(end_val14, step_val14); hv_i += step_val14)
		{
			//
			//Display the InterDistance between the edge pairs.
			hv_Text = ((const HTuple&)hv_InterDistance)[hv_i];
			p_disp_text_left_of_center(hv_WindowHandle, hv_Text.TupleString(".2f"), HTuple(hv_RowEdgeSecond[hv_i]),
				HTuple(hv_ColumnEdgeSecond[hv_i]), HTuple(hv_RowEdgeFirst[hv_i + 1]), HTuple(hv_ColumnEdgeFirst[hv_i + 1]),
				hv_Phi, 2.0*hv_Length);
		}
	}
	return;
}
NON_RETURN HALCON_FUNC_YDS::get_tmp_dir(HTuple *hv_LocalTemp)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_FileExists;

	TupleEnvironment("TEMP", &(*hv_LocalTemp));
	if (0 != ((*hv_LocalTemp) == HTuple("")))
	{
		TupleEnvironment("TMP", &(*hv_LocalTemp));
		if (0 != ((*hv_LocalTemp) == HTuple("")))
		{
			FileExists("/tmp", &hv_FileExists);
			if (0 != hv_FileExists)
			{
				(*hv_LocalTemp) = "/tmp";
			}
			else
			{
				(*hv_LocalTemp) = "./";
			}
		}
	}
	return;
}
NON_RETURN HALCON_FUNC_YDS::gen_initial_trainfile(HTuple hv_TrainFileName)
{

	// Local iconic variables
	HObject  ho_Image, ho_Region, ho_RegionDilation;
	HObject  ho_ConnectedRegions, ho_RegionIntersection, ho_Characters;

	// Local control variables
	HTuple  hv_UsedThreshold, hv_Number, hv_Classes;
	HTuple  hv_J;

	ReadImage(&ho_Image, "letters");
	//Segment the image.
	BinaryThreshold(ho_Image, &ho_Region, "max_separability", "dark", &hv_UsedThreshold);
	//Connect the i's and j's with their dots.
	DilationCircle(ho_Region, &ho_RegionDilation, 3.5);
	//Compute the correct connected components.
	Connection(ho_RegionDilation, &ho_ConnectedRegions);
	//Reduce each connected component (character) to its original shape.
	Intersection(ho_ConnectedRegions, ho_Region, &ho_RegionIntersection);
	//Sort the characters line-by-line.
	SortRegion(ho_RegionIntersection, &ho_Characters, "character", "true", "row");
	//Compute the true class of each character.
	CountObj(ho_Characters, &hv_Number);
	hv_Classes = HTuple();
	for (hv_J = 0; hv_J <= 25; hv_J += 1)
	{
		hv_Classes = hv_Classes.TupleConcat(HTuple(20, ((HTuple("a").TupleOrd()) + hv_J).TupleChr()));
	}
	hv_Classes = hv_Classes.TupleConcat(HTuple(20, "."));
	//Construct the necessary training file from the segmented characters.
	WriteOcrTrainf(ho_Characters, ho_Image, hv_Classes, hv_TrainFileName);
	return;
}


NON_RETURN HALCON_FUNC_YDS::INIT_CAMERA_WINDOW(Hlong lWWindowID)
{
	//********************************************************************************************************
	//***********************************机器视觉***********************************************************
	//*********************************************************************************************************

	//***********************************变量初始化*********************************************************************
	//Camera
	hv_AcqHandle_of_camera = 0;

	//*WINDOW
	hv_Width_of_window = 0;
	hv_Height_of_window = 0;

	hv_PATH_OF_PICTURE1 = "C:/Users/Administrator/Desktop/HALCON工程/TESTING1.bmp";
	hv_PATH_OF_PICTURE2 = "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/NCC_MODEL/ncc_model_demo_01.bmp";
	hv_PATH_OF_PICTURE3 = "C:/Users/Administrator/Desktop/HALCON工程/TES7TING3.bmp";
	hv_PATH_OF_PICTURE5 = "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/NCC_MODEL/ncc_model_demo_02.bmp";
	hv_PATH_OF_PICTURE4 = "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/NCC_MODEL/95A58PICagp_1024.png";
	hv_PATH_OF_PICTURE6 = "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/NCC_MODEL/9077d7b44aed2e73a43d9aa68101a18b86d6fa75.gif";

	//**标志位*****程序是否正常运行*****
	hv_FLAG_ING_ADJUST_YES_OR_NO_YDS = 0;
	hv_FLAG_ING_RECOGNIYION_YES_OR_NO_YDS = 0;

	//***********************************相机的初始化*********************************************************************

	//Image Acquisition 01: Code generated by Image Acquisition 01
	OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "gray", -1, "false",
		"default", "[0]  Camera MV-U130M#3DF11190-3", 0, -1, &hv_AcqHandle_of_camera);
	GrabImageStart(hv_AcqHandle_of_camera, -1);
	ReadImage(&ho_IMAGE_OF_INIT, hv_PATH_OF_PICTURE5);
	ReadImage(&ho_IMAGE_OF_INIT_jiazaizhng, hv_PATH_OF_PICTURE4);
	GetImageSize(ho_IMAGE_OF_INIT, &hv_Width_of_window, &hv_Height_of_window);

	SetWindowAttr("background_color", "black");
	OpenWindow(150, 340, hv_Width_of_window / 3.5, hv_Height_of_window /3.5, lWWindowID, "", "", &hv_WindowHandle);
	HDevWindowStack::Push(hv_WindowHandle);
	//dump_window (3600, 'jpeg', 'C:/Users/Administrator/Desktop/HALCON工程/Template')
	if (HDevWindowStack::IsOpen())
		DispObj(ho_IMAGE_OF_INIT_jiazaizhng, HDevWindowStack::GetActive());


	//*****************************************NCC区域选择以及初始化***************************************************************

	//**矩形的位置选择
	GenRectangle1(&ho_ROI_0, 77.5, 287.5, 895.5, 937.5);     // 8092芯片
																				//GenRectangle1(&ho_ROI_0, 131.5, 305.5, 967.5, 973.5);  //  7314芯片
																				//GenRectangle1(&ho_ROI_0, 172.514, 343.75, 939.005, 946.662); // 856芯片
	AreaCenter(ho_ROI_0, &hv_Area, &hv_RowRef, &hv_ColumnRef);
	ReduceDomain(ho_IMAGE_OF_INIT, ho_ROI_0, &ho_ImageReduced);
	CreateNccModel(ho_ImageReduced, "auto", 0, 0, "auto", "use_polarity", &hv_ModelID);

	//**定义区域填充模式
	/*
	if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(), "margin");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_ROI_0, HDevWindowStack::GetActive());
*/
	hv_Rows = HTuple();
	hv_Cols = HTuple();

}
NON_RETURN HALCON_FUNC_YDS::INIT_OCR_CLASS_SVM()
{
	hv_Rank_sop_8_num1.Clear();
	hv_Rank_sop_8_num1[0] = 0;
	hv_Rank_sop_8_num1[1] = 0;
	hv_Rank_sop_8_num1[2] = 0;
	hv_Rank_sop_8_num1[3] = 0;
	hv_Rank_sop_8_num1[4] = 0;
	hv_Rank_sop_8_num1[5] = 0;
	hv_Rank_sop_8_num1[6] = 0;
	hv_Rank_sop_8_num1[7] = 0;
	hv_Rank_sop_8_num1[8] = 0;
	hv_Rank_sop_8_num1[9] = 0;
	hv_Rank_sop_8_num1[10] = 0;
	hv_Rank_sop_8_num1[11] = 0;
	hv_Rank_sop_8_num1[12] = 0;
	hv_Rank_sop_8_num1[13] = 0;
	hv_Rank_sop_8_num1[14] = 0;
	hv_Rank_sop_8_num1[15] = 0;
	hv_Rank_sop_8_num1[16] = 0;
	hv_Rank_sop_8_num1[17] = 0;
	hv_Rank_sop_8_num1[18] = 0;
	hv_ObjectSelected_all = 0;
	//**OCR分类器获取*********************************
	hv_FontFile = "C:/Users/Administrator/Desktop/HALCON工程/train_characters_ocr_sop_8_num1_8092.omc";
	ReadOcrClassSvm(hv_FontFile, &hv_OCRHandle);

	//清楚界面的内容
	//	if (HDevWindowStack::IsOpen())
	//		ClearWindow(HDevWindowStack::GetActive());
}
NON_RETURN HALCON_FUNC_YDS::ACTION_NCC_MODEL(void)
{
	GrabImageAsync(&ho_Image_temp, hv_AcqHandle_of_camera, -1);
	//dump_window (3601, 'bmp', 'C:/Users/Administrator/Desktop/HALCON工程/TESTING')
	//**根据NCC-Model 找到最佳的匹配的区域
	FindNccModel(ho_Image_temp, hv_ModelID, 0, 0, 0.5, 1, 0.5, "true", 0, &hv_Row,
		&hv_Column, &hv_Angle, &hv_Score);
}
NON_RETURN HALCON_FUNC_YDS::ACTION_FIND_OBJECT_YES_OR_NO(void)
{
	GrabImageAsync(&ho_Image_temp, hv_AcqHandle_of_camera, -1);
	//dump_window (3601, 'bmp', 'C:/Users/Administrator/Desktop/HALCON工程/TESTING')
	//**根据NCC-Model 找到最佳的匹配的区域
	FindNccModel(ho_Image_temp, hv_ModelID, 0, 0, 0.5, 1, 0.5, "true", 0, &hv_Row,
		&hv_Column, &hv_Angle, &hv_Score);
	set_display_font(hv_WindowHandle, 16, "mono", "true", "false");
	disp_message(hv_WindowHandle, "目标物体在视野中不存在或者偏离！！", "image",
		450, 120, "black", "true");
	disp_message(hv_WindowHandle, "提示：请将物体移动至视野中！！", "image", 516,
		120, "black", "true");
	set_display_font(hv_WindowHandle, 16, "mono", "true", "false");
	disp_message(hv_WindowHandle, "工作状态：目标偏离", "image", 0, 0, "green",
		"false");
}
NON_RETURN HALCON_FUNC_YDS::ACTION_CONFIRM_OBJECT(void)
{
	VectorAngleToRigid(hv_RowRef, hv_ColumnRef, 0, hv_Row, hv_Column, 0, &hv_HomMat2D);
	//disp_message (WindowHandle, ' testing: ', 'window', Row, 0, 'lime green', 'false')
	AffineTransRegion(ho_ROI_0, &ho_RegionAffineTrans, hv_HomMat2D, "nearest_neighbor");
	hv_Rows = hv_Rows.TupleConcat(hv_Row);
	hv_Cols = hv_Cols.TupleConcat(hv_Column);

	//****目标区域位置的选定*******************
	if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(), "margin");
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "red");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_RegionAffineTrans, HDevWindowStack::GetActive());
	//******************************芯片凹原点检测**************************************************************************

	if (HDevWindowStack::IsOpen())
		DispObj(ho_Image_temp, HDevWindowStack::GetActive());
	hv_point_yds_row = hv_Row + 133;
	hv_point_yds_col = hv_Column - 230;
	GenCircle(&ho_Circle, hv_point_yds_row, hv_point_yds_col, 35);
}
NON_RETURN HALCON_FUNC_YDS::INIT_LOCATION_CHAR_AND_LOGO(void)
{
	//**FOR CHAR shibie
	hv_point_yds_row_crop = hv_Row - 238;
	hv_point_yds_column_crop = hv_Column - 298;
	hv_point_yds_width_crop = 596;
	hv_point_yds_height_crop = 448;
}
NON_RETURN HALCON_FUNC_YDS::INIT_LOCATION_PIN(void)
{
	//**define for MeasureHandle1
	hv_point_yds_row1 = hv_Row + 350;
	hv_point_yds_column1 = hv_Column;
	hv_point_yds_phi1 = 0;
	//**define for MeasureHandle1 AND MeasureHandle2
	hv_point_yds_Length1 = 298;
	hv_point_yds_Length2 = 15;
	//**define for MeasureHandle2
	hv_point_yds_row2 = hv_Row - 360;
	hv_point_yds_column2 = hv_Column;
	hv_point_yds_phi2 = 0 - (HTuple(180).TupleRad());

	//**define for MeasureHandle3
	hv_point_yds_row3 = hv_Row;
	hv_point_yds_column3 = hv_Column;
	hv_point_yds_phi3 = HTuple(-90).TupleRad();
	hv_point_yds_Length3 = 410;
	hv_point_yds_Length4 = 298;

	//**define for MeasureHandle3
	hv_point_yds_row4 = hv_Row + 260;
	hv_point_yds_column4 = hv_Column;
	hv_point_yds_phi4 = hv_Angle;

	//**define for MeasureHandle4
	hv_point_yds_row5 = hv_Row - 270;
	hv_point_yds_column5 = hv_Column;
	hv_point_yds_phi5 = hv_Angle - (HTuple(180).TupleRad());

	//**芯片管脚的长度8个
	hv_point_yds_Length5 = 90;
	hv_point_yds_Length6 = 15;

	//**define for MeasureHandle11
	hv_point_yds_row11 = hv_Row + 305;
	hv_point_yds_column11 = hv_Column - 235;
	hv_point_yds_phi11 = HTuple(90).TupleRad();

	//**define for MeasureHandle12
	hv_point_yds_row12 = hv_Row + 305;
	hv_point_yds_column12 = hv_Column - 75;
	hv_point_yds_phi12 = HTuple(90).TupleRad();
	//stop ()
	//**define for MeasureHandle13
	hv_point_yds_row13 = hv_Row + 305;
	hv_point_yds_column13 = hv_Column + 85;
	hv_point_yds_phi13 = HTuple(90).TupleRad();

	//**define for MeasureHandle14
	hv_point_yds_row14 = hv_Row + 305;
	hv_point_yds_column14 = hv_Column + 245;
	hv_point_yds_phi14 = HTuple(90).TupleRad();
	//**define for MeasureHandle15
	hv_point_yds_row15 = hv_Row - 305;
	hv_point_yds_column15 = hv_Column - 235;
	hv_point_yds_phi15 = HTuple(90).TupleRad();
	//**define for MeasureHandle16
	hv_point_yds_row16 = hv_Row - 305;
	hv_point_yds_column16 = hv_Column - 75;
	hv_point_yds_phi16 = HTuple(90).TupleRad();
	//**define for MeasureHandle17
	hv_point_yds_row17 = hv_Row - 305;
	hv_point_yds_column17 = hv_Column + 85;
	hv_point_yds_phi17 = HTuple(90).TupleRad();
	//**define for MeasureHandle18
	hv_point_yds_row18 = hv_Row - 305;
	hv_point_yds_column18 = hv_Column + 245;
	hv_point_yds_phi18 = HTuple(90).TupleRad();

}
NON_RETURN HALCON_FUNC_YDS::INIT_FONT_PIN(void)
{
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "green");
	if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(), "margin");
	if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(), 3);
	set_display_font(hv_WindowHandle, 14, "mono", "true", "false");
}
NON_RETURN HALCON_FUNC_YDS::ACTION_MEASURE_PIN(void)
{
	//测量方案 1 - 2 
	GenMeasureRectangle2(hv_point_yds_row1, hv_point_yds_column1, hv_point_yds_phi1,
		hv_point_yds_Length1, hv_point_yds_Length2, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle1);
	GenMeasureRectangle2(hv_point_yds_row2, hv_point_yds_column2, hv_point_yds_phi2,
		hv_point_yds_Length1, hv_point_yds_Length2, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle2);
	//测量方案 3 （暂时可能还没有用到）
	GenMeasureRectangle2(hv_point_yds_row3, hv_point_yds_column3, hv_point_yds_phi3,
		hv_point_yds_Length3, hv_point_yds_Length4, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle3);
	//新增的两个测量方案 4 - 5 
	GenMeasureRectangle2(hv_point_yds_row4, hv_point_yds_column4, hv_point_yds_phi4,
		hv_point_yds_Length1, hv_point_yds_Length2, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle4);
	GenMeasureRectangle2(hv_point_yds_row5, hv_point_yds_column5, hv_point_yds_phi5,
		hv_point_yds_Length1, hv_point_yds_Length2, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle5);
	// 11 - 18 管脚 的测量
	GenMeasureRectangle2(hv_point_yds_row11, hv_point_yds_column11, hv_point_yds_phi11,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle11);
	GenMeasureRectangle2(hv_point_yds_row12, hv_point_yds_column12, hv_point_yds_phi12,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle12);
	GenMeasureRectangle2(hv_point_yds_row13, hv_point_yds_column13, hv_point_yds_phi13,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle13);
	GenMeasureRectangle2(hv_point_yds_row14, hv_point_yds_column14, hv_point_yds_phi14,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle14);
	GenMeasureRectangle2(hv_point_yds_row15, hv_point_yds_column15, hv_point_yds_phi15,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle15);
	GenMeasureRectangle2(hv_point_yds_row16, hv_point_yds_column16, hv_point_yds_phi16,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle16);
	GenMeasureRectangle2(hv_point_yds_row17, hv_point_yds_column17, hv_point_yds_phi17,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle17);
	GenMeasureRectangle2(hv_point_yds_row18, hv_point_yds_column18, hv_point_yds_phi18,
		hv_point_yds_Length5, hv_point_yds_Length6, hv_Width_of_window, hv_Height_of_window,
		"nearest_neighbor", &hv_MeasureHandle18);
	//11 - 18 管脚测量
	MeasurePos(ho_Image_temp, hv_MeasureHandle11, 10, 80, "all", "all", &hv_RowEdge11,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance11);
	MeasurePos(ho_Image_temp, hv_MeasureHandle12, 10, 80, "all", "all", &hv_RowEdge12,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance12);
	MeasurePos(ho_Image_temp, hv_MeasureHandle13, 10, 80, "all", "all", &hv_RowEdge13,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance13);
	MeasurePos(ho_Image_temp, hv_MeasureHandle14, 10, 80, "all", "all", &hv_RowEdge14,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance14);
	MeasurePos(ho_Image_temp, hv_MeasureHandle15, 10, 80, "all", "all", &hv_RowEdge15,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance15);
	MeasurePos(ho_Image_temp, hv_MeasureHandle16, 10, 80, "all", "all", &hv_RowEdge16,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance16);
	MeasurePos(ho_Image_temp, hv_MeasureHandle17, 10, 80, "all", "all", &hv_RowEdge17,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance17);
	MeasurePos(ho_Image_temp, hv_MeasureHandle18, 10, 80, "all", "all", &hv_RowEdge18,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance18);
	MeasurePos(ho_Image_temp, hv_MeasureHandle3, 1.5, 30, "all", "all", &hv_RowEdge,
		&hv_ColumnEdge, &hv_Amplitude, &hv_Distance);
	//测量管脚跨距
	int ddddd;
	ddddd = hv_RowEdge11.TupleLength()+ hv_RowEdge12.TupleLength() + hv_RowEdge13.TupleLength() + hv_RowEdge14.TupleLength()
		+ hv_RowEdge15.TupleLength() + hv_RowEdge16.TupleLength() + hv_RowEdge17.TupleLength() + hv_RowEdge18.TupleLength();

		hv_SPAN_OF_CHIP_1 = HTuple(hv_RowEdge11[0]) - HTuple(hv_RowEdge18[1]);
		hv_SPAN_OF_CHIP_2 = HTuple(hv_RowEdge12[0]) - HTuple(hv_RowEdge17[1]);
		hv_SPAN_OF_CHIP_3 = HTuple(hv_RowEdge13[0]) - HTuple(hv_RowEdge16[1]);
		hv_SPAN_OF_CHIP_4 = HTuple(hv_RowEdge14[0]) - HTuple(hv_RowEdge15[1]);

	//保证测量（两个差异灰度）
	if (0 != ((hv_Distance11.TupleLength()) == 2))
	{
		hv_Distance11 = HTuple(hv_Distance11[0]) + HTuple(hv_Distance11[1]);
	}
	if (0 != ((hv_Distance12.TupleLength()) == 2))
	{
		hv_Distance12 = HTuple(hv_Distance12[0]) + HTuple(hv_Distance12[1]);
	}
	if (0 != ((hv_Distance13.TupleLength()) == 2))
	{
		hv_Distance13 = HTuple(hv_Distance13[0]) + HTuple(hv_Distance13[1]);
	}
	if (0 != ((hv_Distance14.TupleLength()) == 2))
	{
		hv_Distance14 = HTuple(hv_Distance14[0]) + HTuple(hv_Distance14[1]);
	}
	if (0 != ((hv_Distance15.TupleLength()) == 2))
	{
		hv_Distance15 = HTuple(hv_Distance15[0]) + HTuple(hv_Distance15[1]);
	}
	if (0 != ((hv_Distance16.TupleLength()) == 2))
	{
		hv_Distance16 = HTuple(hv_Distance16[0]) + HTuple(hv_Distance16[1]);
	}
	if (0 != ((hv_Distance17.TupleLength()) == 2))
	{
		hv_Distance17 = HTuple(hv_Distance17[0]) + HTuple(hv_Distance17[1]);
	}
	if (0 != ((hv_Distance18.TupleLength()) == 2))
	{
		hv_Distance18 = HTuple(hv_Distance18[0]) + HTuple(hv_Distance18[1]);
	}
	//保证测量（三个差异灰度）
	if (0 != ((hv_Distance11.TupleLength()) == 3))
	{
		hv_Distance11 = HTuple(hv_Distance11[0]) + HTuple(hv_Distance11[1]) + HTuple(hv_Distance11[2]);
	}
	if (0 != ((hv_Distance12.TupleLength()) == 3))
	{
		hv_Distance12 = HTuple(hv_Distance12[0]) + HTuple(hv_Distance12[1]) + HTuple(hv_Distance12[2]);
	}
	if (0 != ((hv_Distance13.TupleLength()) == 3))
	{
		hv_Distance13 = HTuple(hv_Distance13[0]) + HTuple(hv_Distance13[1]) + HTuple(hv_Distance13[2]);
	}
	if (0 != ((hv_Distance14.TupleLength()) == 3))
	{
		hv_Distance14 = HTuple(hv_Distance14[0]) + HTuple(hv_Distance14[1]) + HTuple(hv_Distance14[2]);
	}
	if (0 != ((hv_Distance15.TupleLength()) == 3))
	{
		hv_Distance15 = HTuple(hv_Distance15[0]) + HTuple(hv_Distance15[1]) + HTuple(hv_Distance15[2]);
	}
	if (0 != ((hv_Distance16.TupleLength()) == 3))
	{
		hv_Distance16 = HTuple(hv_Distance16[0]) + HTuple(hv_Distance16[1]) + HTuple(hv_Distance16[2]);
	}
	if (0 != ((hv_Distance17.TupleLength()) == 3))
	{
		hv_Distance17 = HTuple(hv_Distance17[0]) + HTuple(hv_Distance17[1]) + HTuple(hv_Distance17[2]);
	}
	if (0 != ((hv_Distance18.TupleLength()) == 3))
	{
		hv_Distance18 = HTuple(hv_Distance18[0]) + HTuple(hv_Distance18[1]) + HTuple(hv_Distance18[2]);
	}


	hv_FLAG_ING_ADJUST_YES_OR_NO_YDS = 0;
			MeasurePairs(ho_Image_temp, hv_MeasureHandle1, 1.5, 30, "positive_strongest",
				"all", &hv_RowEdgeFirst1, &hv_ColumnEdgeFirst1, &hv_AmplitudeFirst1, &hv_RowEdgeSecond1,
				&hv_ColumnEdgeSecond1, &hv_AmplitudeSecond1, &hv_PinWidth1, &hv_PinDistance1);
			MeasurePairs(ho_Image_temp, hv_MeasureHandle2, 1.5, 30, "positive_strongest",
				"all", &hv_RowEdgeFirst2, &hv_ColumnEdgeFirst2, &hv_AmplitudeFirst2, &hv_RowEdgeSecond2,
				&hv_ColumnEdgeSecond2, &hv_AmplitudeSecond2, &hv_PinWidth2, &hv_PinDistance2);
			MeasurePairs(ho_Image_temp, hv_MeasureHandle4, 1.5, 30, "positive_strongest",
				"all", &hv_RowEdgeFirst4, &hv_ColumnEdgeFirst4, &hv_AmplitudeFirst4, &hv_RowEdgeSecond4,
				&hv_ColumnEdgeSecond4, &hv_AmplitudeSecond4, &hv_PinWidth4, &hv_PinDistance4);
			MeasurePairs(ho_Image_temp, hv_MeasureHandle5, 1.5, 30, "positive_strongest",
				"all", &hv_RowEdgeFirst5, &hv_ColumnEdgeFirst5, &hv_AmplitudeFirst5, &hv_RowEdgeSecond5,
				&hv_ColumnEdgeSecond5, &hv_AmplitudeSecond5, &hv_PinWidth5, &hv_PinDistance5);
			//if (0 != ((hv_RowEdgeFirst1.TupleLength()) == 4))
			int AAAAA,BBBBB,CCCCC;
			AAAAA = hv_RowEdgeFirst4.TupleLength() + hv_ColumnEdgeFirst4.TupleLength() + hv_RowEdgeFirst1.TupleLength() + hv_ColumnEdgeFirst1.TupleLength() 
				+ hv_RowEdgeFirst2.TupleLength() + hv_ColumnEdgeFirst2.TupleLength() + hv_RowEdgeFirst5.TupleLength() + hv_ColumnEdgeFirst5.TupleLength();
			if (AAAAA == 32)
			{
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst4[0]), HTuple(hv_ColumnEdgeFirst4[0]),
					HTuple(hv_RowEdgeFirst1[0]), HTuple(hv_ColumnEdgeFirst1[0]), &hv_ANGLE_OF_PIN1);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst4[1]), HTuple(hv_ColumnEdgeFirst4[1]),
					HTuple(hv_RowEdgeFirst1[1]), HTuple(hv_ColumnEdgeFirst1[1]), &hv_ANGLE_OF_PIN2);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst4[2]), HTuple(hv_ColumnEdgeFirst4[2]),
					HTuple(hv_RowEdgeFirst1[2]), HTuple(hv_ColumnEdgeFirst1[2]), &hv_ANGLE_OF_PIN3);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst4[3]), HTuple(hv_ColumnEdgeFirst4[3]),
					HTuple(hv_RowEdgeFirst1[3]), HTuple(hv_ColumnEdgeFirst1[3]), &hv_ANGLE_OF_PIN4);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst2[0]), HTuple(hv_ColumnEdgeFirst2[0]),
					HTuple(hv_RowEdgeFirst5[0]), HTuple(hv_ColumnEdgeFirst5[0]), &hv_ANGLE_OF_PIN5);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst2[1]), HTuple(hv_ColumnEdgeFirst2[1]),
					HTuple(hv_RowEdgeFirst5[1]), HTuple(hv_ColumnEdgeFirst5[1]), &hv_ANGLE_OF_PIN6);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst2[2]), HTuple(hv_ColumnEdgeFirst2[2]),
					HTuple(hv_RowEdgeFirst5[2]), HTuple(hv_ColumnEdgeFirst5[2]), &hv_ANGLE_OF_PIN7);
				AngleLl(0, 0, 1, 0, HTuple(hv_RowEdgeFirst2[3]), HTuple(hv_ColumnEdgeFirst2[3]),
					HTuple(hv_RowEdgeFirst5[3]), HTuple(hv_ColumnEdgeFirst5[3]), &hv_ANGLE_OF_PIN8);
			}
			BBBBB = hv_RowEdgeSecond5.TupleLength() + hv_ColumnEdgeSecond5.TupleLength() + hv_RowEdgeFirst4.TupleLength() + hv_ColumnEdgeFirst4.TupleLength()
				+ hv_RowEdgeFirst1.TupleLength() + hv_ColumnEdgeFirst1.TupleLength();
			if (BBBBB == 24)
			{
				//*quanqingxie
				AngleLl(HTuple(hv_RowEdgeSecond5[3]), HTuple(hv_ColumnEdgeSecond5[3]), HTuple(hv_RowEdgeFirst4[0]),
					HTuple(hv_ColumnEdgeFirst4[0]), HTuple(hv_RowEdgeFirst4[0]), HTuple(hv_ColumnEdgeFirst4[0]),
					HTuple(hv_RowEdgeFirst1[0]), HTuple(hv_ColumnEdgeFirst1[0]), &hv_ANGLE_OF_INC_PIN1);
				AngleLl(HTuple(hv_RowEdgeSecond5[2]), HTuple(hv_ColumnEdgeSecond5[2]), HTuple(hv_RowEdgeFirst4[1]),
					HTuple(hv_ColumnEdgeFirst4[1]), HTuple(hv_RowEdgeFirst4[1]), HTuple(hv_ColumnEdgeFirst4[1]),
					HTuple(hv_RowEdgeFirst1[1]), HTuple(hv_ColumnEdgeFirst1[1]), &hv_ANGLE_OF_INC_PIN2);
				AngleLl(HTuple(hv_RowEdgeSecond5[1]), HTuple(hv_ColumnEdgeSecond5[1]), HTuple(hv_RowEdgeFirst4[2]),
					HTuple(hv_ColumnEdgeFirst4[2]), HTuple(hv_RowEdgeFirst4[2]), HTuple(hv_ColumnEdgeFirst4[2]),
					HTuple(hv_RowEdgeFirst1[2]), HTuple(hv_ColumnEdgeFirst1[2]), &hv_ANGLE_OF_INC_PIN3);
				AngleLl(HTuple(hv_RowEdgeSecond5[0]), HTuple(hv_ColumnEdgeSecond5[0]), HTuple(hv_RowEdgeFirst4[3]),
					HTuple(hv_ColumnEdgeFirst4[3]), HTuple(hv_RowEdgeFirst4[3]), HTuple(hv_ColumnEdgeFirst4[3]),
					HTuple(hv_RowEdgeFirst1[3]), HTuple(hv_ColumnEdgeFirst1[3]), &hv_ANGLE_OF_INC_PIN4);
				AngleLl(HTuple(hv_RowEdgeSecond5[3]), HTuple(hv_ColumnEdgeSecond5[3]), HTuple(hv_RowEdgeFirst4[0]),
					HTuple(hv_ColumnEdgeFirst4[0]), HTuple(hv_RowEdgeFirst2[3]), HTuple(hv_ColumnEdgeFirst2[3]),
					HTuple(hv_RowEdgeFirst5[3]), HTuple(hv_ColumnEdgeFirst5[3]), &hv_ANGLE_OF_INC_PIN8);
				AngleLl(HTuple(hv_RowEdgeSecond5[2]), HTuple(hv_ColumnEdgeSecond5[2]), HTuple(hv_RowEdgeFirst4[1]),
					HTuple(hv_ColumnEdgeFirst4[1]), HTuple(hv_RowEdgeFirst2[2]), HTuple(hv_ColumnEdgeFirst2[2]),
					HTuple(hv_RowEdgeFirst5[2]), HTuple(hv_ColumnEdgeFirst5[2]), &hv_ANGLE_OF_INC_PIN7);
				AngleLl(HTuple(hv_RowEdgeSecond5[1]), HTuple(hv_ColumnEdgeSecond5[1]), HTuple(hv_RowEdgeFirst4[2]),
					HTuple(hv_ColumnEdgeFirst4[2]), HTuple(hv_RowEdgeFirst2[1]), HTuple(hv_ColumnEdgeFirst2[1]),
					HTuple(hv_RowEdgeFirst5[1]), HTuple(hv_ColumnEdgeFirst5[1]), &hv_ANGLE_OF_INC_PIN6);
				AngleLl(HTuple(hv_RowEdgeSecond5[0]), HTuple(hv_ColumnEdgeSecond5[0]), HTuple(hv_RowEdgeFirst4[3]),
					HTuple(hv_ColumnEdgeFirst4[3]), HTuple(hv_RowEdgeFirst2[0]), HTuple(hv_ColumnEdgeFirst2[0]),
					HTuple(hv_RowEdgeFirst5[0]), HTuple(hv_ColumnEdgeFirst5[0]), &hv_ANGLE_OF_INC_PIN5);
			}

			if (0 != (hv_ANGLE_OF_PIN1<0))
			{
				hv_ANGLE_OF_PIN1 = -hv_ANGLE_OF_PIN1;
			}
			if (0 != (hv_ANGLE_OF_PIN2<0))
			{
				hv_ANGLE_OF_PIN2 = -hv_ANGLE_OF_PIN2;
			}
			if (0 != (hv_ANGLE_OF_PIN3<0))
			{
				hv_ANGLE_OF_PIN3 = -hv_ANGLE_OF_PIN3;
			}
			if (0 != (hv_ANGLE_OF_PIN4<0))
			{
				hv_ANGLE_OF_PIN4 = -hv_ANGLE_OF_PIN4;
			}
			if (0 != (hv_ANGLE_OF_PIN5<0))
			{
				hv_ANGLE_OF_PIN5 = -hv_ANGLE_OF_PIN5;
			}
			if (0 != (hv_ANGLE_OF_PIN6<0))
			{
				hv_ANGLE_OF_PIN6 = -hv_ANGLE_OF_PIN6;
			}
			if (0 != (hv_ANGLE_OF_PIN7<0))
			{
				hv_ANGLE_OF_PIN7 = -hv_ANGLE_OF_PIN7;
			}
			if (0 != (hv_ANGLE_OF_PIN8<0))
			{
				hv_ANGLE_OF_PIN8 = -hv_ANGLE_OF_PIN8;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN1<0))
			{
				hv_ANGLE_OF_INC_PIN1 = -hv_ANGLE_OF_INC_PIN1;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN2<0))
			{
				hv_ANGLE_OF_INC_PIN2 = -hv_ANGLE_OF_INC_PIN2;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN3<0))
			{
				hv_ANGLE_OF_INC_PIN3 = -hv_ANGLE_OF_INC_PIN3;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN4<0))
			{
				hv_ANGLE_OF_INC_PIN4 = -hv_ANGLE_OF_INC_PIN4;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN5<0))
			{
				hv_ANGLE_OF_INC_PIN5 = -hv_ANGLE_OF_INC_PIN5;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN6<0))
			{
				hv_ANGLE_OF_INC_PIN6 = -hv_ANGLE_OF_INC_PIN6;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN7<0))
			{
				hv_ANGLE_OF_INC_PIN7 = -hv_ANGLE_OF_INC_PIN7;
			}
			if (0 != (hv_ANGLE_OF_INC_PIN8<0))
			{
				hv_ANGLE_OF_INC_PIN8 = -hv_ANGLE_OF_INC_PIN8;
			}
			CCCCC = hv_PinWidth1.TupleLength() + hv_PinWidth2.TupleLength() + hv_Distance11.TupleLength() + hv_Distance12.TupleLength() + hv_Distance13.TupleLength()
				+ hv_Distance14.TupleLength() + hv_Distance15.TupleLength() + hv_Distance16.TupleLength() + hv_Distance17.TupleLength() + hv_Distance18.TupleLength();
			if (CCCCC == 16)
			{
				hv_CURVA_DISTANCE_OF_PIN1 = ((hv_ANGLE_OF_PIN1.TupleSin())*hv_Distance11) + (HTuple(hv_PinWidth1[0]) / 2);
				hv_CURVA_DISTANCE_OF_PIN2 = ((hv_ANGLE_OF_PIN2.TupleSin())*hv_Distance12) + (HTuple(hv_PinWidth1[1]) / 2);
				hv_CURVA_DISTANCE_OF_PIN3 = ((hv_ANGLE_OF_PIN3.TupleSin())*hv_Distance13) + (HTuple(hv_PinWidth1[2]) / 2);
				hv_CURVA_DISTANCE_OF_PIN4 = ((hv_ANGLE_OF_PIN4.TupleSin())*hv_Distance14) + (HTuple(hv_PinWidth1[3]) / 2);
				hv_CURVA_DISTANCE_OF_PIN5 = ((hv_ANGLE_OF_PIN5.TupleSin())*hv_Distance15) + (HTuple(hv_PinWidth2[0]) / 2);
				hv_CURVA_DISTANCE_OF_PIN6 = ((hv_ANGLE_OF_PIN6.TupleSin())*hv_Distance16) + (HTuple(hv_PinWidth2[1]) / 2);
				hv_CURVA_DISTANCE_OF_PIN7 = ((hv_ANGLE_OF_PIN7.TupleSin())*hv_Distance17) + (HTuple(hv_PinWidth2[2]) / 2);
				hv_CURVA_DISTANCE_OF_PIN8 = ((hv_ANGLE_OF_PIN8.TupleSin())*hv_Distance18) + (HTuple(hv_PinWidth2[3]) / 2);

				hv_CURVA_DISTANCE_OF_INC_PIN1 = ((hv_ANGLE_OF_INC_PIN1.TupleSin())*hv_Distance11) + (HTuple(hv_PinWidth1[0]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN2 = ((hv_ANGLE_OF_INC_PIN2.TupleSin())*hv_Distance12) + (HTuple(hv_PinWidth1[1]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN3 = ((hv_ANGLE_OF_INC_PIN3.TupleSin())*hv_Distance13) + (HTuple(hv_PinWidth1[2]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN4 = ((hv_ANGLE_OF_INC_PIN4.TupleSin())*hv_Distance14) + (HTuple(hv_PinWidth1[3]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN5 = ((hv_ANGLE_OF_INC_PIN5.TupleSin())*hv_Distance15) + (HTuple(hv_PinWidth2[0]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN6 = ((hv_ANGLE_OF_INC_PIN6.TupleSin())*hv_Distance16) + (HTuple(hv_PinWidth2[1]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN7 = ((hv_ANGLE_OF_INC_PIN7.TupleSin())*hv_Distance17) + (HTuple(hv_PinWidth2[2]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN8 = ((hv_ANGLE_OF_INC_PIN8.TupleSin())*hv_Distance18) + (HTuple(hv_PinWidth2[3]) / 2);
			}
			else
			{
				hv_PinWidth1[0] = 0;
				hv_PinWidth1[1] = 0;
				hv_PinWidth1[2] = 0;
				hv_PinWidth1[3] = 0;
				hv_PinWidth2[0] = 0;
				hv_PinWidth2[1] = 0;
				hv_PinWidth2[3] = 0;
				hv_PinWidth2[2] = 0;
				hv_Distance11 = 0;
				hv_Distance12 = 0;
				hv_Distance13 = 0;
				hv_Distance14 = 0;
				hv_Distance15 = 0;
				hv_Distance16 = 0;
				hv_Distance17 = 0;
				hv_Distance18 = 0;

				
				hv_CURVA_DISTANCE_OF_PIN1 = ((hv_ANGLE_OF_PIN1.TupleSin())*hv_Distance11) + (HTuple(hv_PinWidth1[0]) / 2);
				hv_CURVA_DISTANCE_OF_PIN2 = ((hv_ANGLE_OF_PIN2.TupleSin())*hv_Distance12) + (HTuple(hv_PinWidth1[1]) / 2);
				hv_CURVA_DISTANCE_OF_PIN3 = ((hv_ANGLE_OF_PIN3.TupleSin())*hv_Distance13) + (HTuple(hv_PinWidth1[2]) / 2);
				hv_CURVA_DISTANCE_OF_PIN4 = ((hv_ANGLE_OF_PIN4.TupleSin())*hv_Distance14) + (HTuple(hv_PinWidth1[3]) / 2);
				hv_CURVA_DISTANCE_OF_PIN5 = ((hv_ANGLE_OF_PIN5.TupleSin())*hv_Distance15) + (HTuple(hv_PinWidth2[0]) / 2);
				hv_CURVA_DISTANCE_OF_PIN6 = ((hv_ANGLE_OF_PIN6.TupleSin())*hv_Distance16) + (HTuple(hv_PinWidth2[1]) / 2);
				hv_CURVA_DISTANCE_OF_PIN7 = ((hv_ANGLE_OF_PIN7.TupleSin())*hv_Distance17) + (HTuple(hv_PinWidth2[2]) / 2);
				hv_CURVA_DISTANCE_OF_PIN8 = ((hv_ANGLE_OF_PIN8.TupleSin())*hv_Distance18) + (HTuple(hv_PinWidth2[3]) / 2);

				hv_CURVA_DISTANCE_OF_INC_PIN1 = ((hv_ANGLE_OF_INC_PIN1.TupleSin())*hv_Distance11) + (HTuple(hv_PinWidth1[0]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN2 = ((hv_ANGLE_OF_INC_PIN2.TupleSin())*hv_Distance12) + (HTuple(hv_PinWidth1[1]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN3 = ((hv_ANGLE_OF_INC_PIN3.TupleSin())*hv_Distance13) + (HTuple(hv_PinWidth1[2]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN4 = ((hv_ANGLE_OF_INC_PIN4.TupleSin())*hv_Distance14) + (HTuple(hv_PinWidth1[3]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN5 = ((hv_ANGLE_OF_INC_PIN5.TupleSin())*hv_Distance15) + (HTuple(hv_PinWidth2[0]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN6 = ((hv_ANGLE_OF_INC_PIN6.TupleSin())*hv_Distance16) + (HTuple(hv_PinWidth2[1]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN7 = ((hv_ANGLE_OF_INC_PIN7.TupleSin())*hv_Distance17) + (HTuple(hv_PinWidth2[2]) / 2);
				hv_CURVA_DISTANCE_OF_INC_PIN8 = ((hv_ANGLE_OF_INC_PIN8.TupleSin())*hv_Distance18) + (HTuple(hv_PinWidth2[3]) / 2);

			}

			
			hv_shuzuyuansu_geshu = (((((((hv_RowEdgeFirst1.TupleLength()) + (hv_RowEdgeFirst2.TupleLength())) + (hv_ColumnEdgeFirst1.TupleLength())) + (hv_ColumnEdgeFirst2.TupleLength())) + (hv_RowEdgeSecond1.TupleLength())) + (hv_RowEdgeSecond2.TupleLength())) + (hv_ColumnEdgeSecond1.TupleLength())) + (hv_ColumnEdgeSecond2.TupleLength());
			if (0 != (hv_shuzuyuansu_geshu != 32))
			{
				//**对不符合数据的进行停滞
				//**或者是备份正确的一份数据
				//i := 1
				hv_RowEdgeFirst1 = hv_RowEdgeFirst1_last;
				hv_ColumnEdgeFirst1 = hv_ColumnEdgeFirst1_last;
				hv_AmplitudeFirst1 = hv_AmplitudeFirst1_last;
				hv_RowEdgeSecond1 = hv_RowEdgeSecond1_last;
				hv_ColumnEdgeSecond1 = hv_ColumnEdgeSecond1_last;
				hv_AmplitudeSecond1 = hv_AmplitudeSecond1_last;
				hv_PinWidth1 = hv_PinWidth1_last;
				hv_PinDistance1 = hv_PinDistance1_last;

				hv_RowEdgeFirst2 = hv_RowEdgeFirst2_last;
				hv_ColumnEdgeFirst2 = hv_ColumnEdgeFirst2_last;
				hv_AmplitudeFirst2 = hv_AmplitudeFirst2_last;
				hv_RowEdgeSecond2 = hv_RowEdgeSecond2_last;
				hv_ColumnEdgeSecond2 = hv_ColumnEdgeSecond2_last;
				hv_AmplitudeSecond2 = hv_AmplitudeSecond2_last;
				hv_PinWidth2 = hv_PinWidth2_last;
				hv_PinDistance2 = hv_PinDistance2_last;
				disp_message(hv_WindowHandle, "目标物体正在矫正中......", "image", 450, 120,
					"black", "true");
				set_display_font(hv_WindowHandle, 16, "mono", "true", "false");
				disp_message(hv_WindowHandle, "工作状态：矫正中", "image", 0, 0, "green",
					"false");
			}

	//*************做一个数据的备份，防止在移动物体时，出现数据测量的不准确，导致程序出现BUG**********************
	//*************如果数组中的元素个数不满足的要求的话，将会用以前备份的数据进行初始化***************************

	hv_RowEdgeFirst1_last = hv_RowEdgeFirst1;
	hv_ColumnEdgeFirst1_last = hv_ColumnEdgeFirst1;
	hv_AmplitudeFirst1_last = hv_AmplitudeFirst1;
	hv_RowEdgeSecond1_last = hv_RowEdgeSecond1;
	hv_ColumnEdgeSecond1_last = hv_ColumnEdgeSecond1;
	hv_AmplitudeSecond1_last = hv_AmplitudeSecond1;
	hv_PinWidth1_last = hv_PinWidth1;
	hv_PinDistance1_last = hv_PinDistance1;

	hv_RowEdgeFirst2_last = hv_RowEdgeFirst2;
	hv_ColumnEdgeFirst2_last = hv_ColumnEdgeFirst2;
	hv_AmplitudeFirst2_last = hv_AmplitudeFirst2;
	hv_RowEdgeSecond2_last = hv_RowEdgeSecond2;
	hv_ColumnEdgeSecond2_last = hv_ColumnEdgeSecond2;
	hv_AmplitudeSecond2_last = hv_AmplitudeSecond2;
	hv_PinWidth2_last = hv_PinWidth2;
	hv_PinDistance2_last = hv_PinDistance2;
}
NON_RETURN HALCON_FUNC_YDS::ACTION_BACKUP_DATA_PIN(void)
{
	hv_RowEdgeFirst1_last = hv_RowEdgeFirst1;
	hv_ColumnEdgeFirst1_last = hv_ColumnEdgeFirst1;
	hv_AmplitudeFirst1_last = hv_AmplitudeFirst1;
	hv_RowEdgeSecond1_last = hv_RowEdgeSecond1;
	hv_ColumnEdgeSecond1_last = hv_ColumnEdgeSecond1;
	hv_AmplitudeSecond1_last = hv_AmplitudeSecond1;
	hv_PinWidth1_last = hv_PinWidth1;
	hv_PinDistance1_last = hv_PinDistance1;

	hv_RowEdgeFirst2_last = hv_RowEdgeFirst2;
	hv_ColumnEdgeFirst2_last = hv_ColumnEdgeFirst2;
	hv_AmplitudeFirst2_last = hv_AmplitudeFirst2;
	hv_RowEdgeSecond2_last = hv_RowEdgeSecond2;
	hv_ColumnEdgeSecond2_last = hv_ColumnEdgeSecond2;
	hv_AmplitudeSecond2_last = hv_AmplitudeSecond2;
	hv_PinWidth2_last = hv_PinWidth2;
	hv_PinDistance2_last = hv_PinDistance2;
}
NON_RETURN HALCON_FUNC_YDS::ACTION_CALCULATE_RESULT_OF_PIN(void)
{
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "red");
	hv_RowEdgeFirst1.Clear();
	hv_RowEdgeFirst1.Append(hv_point_yds_row1);
	hv_RowEdgeFirst1.Append(hv_point_yds_row1);
	hv_RowEdgeFirst1.Append(hv_point_yds_row1);
	hv_RowEdgeFirst1.Append(hv_point_yds_row1);
	hv_RowEdgeFirst2.Clear();
	hv_RowEdgeFirst2.Append(hv_point_yds_row2);
	hv_RowEdgeFirst2.Append(hv_point_yds_row2);
	hv_RowEdgeFirst2.Append(hv_point_yds_row2);
	hv_RowEdgeFirst2.Append(hv_point_yds_row2);
	//划线的程序************************************
	//*************只有在程序正常与运行的情况下执行
	if (0 != (hv_FLAG_ING_ADJUST_YES_OR_NO_YDS == 0))
	{
		DispLine(hv_WindowHandle, hv_RowEdgeFirst1, hv_ColumnEdgeFirst1, hv_RowEdgeSecond1,
			hv_ColumnEdgeSecond1);
		DispLine(hv_WindowHandle, hv_RowEdgeFirst2, hv_ColumnEdgeFirst2, hv_RowEdgeSecond2,
			hv_ColumnEdgeSecond2);
	}


	hv_avgPinWidth1 = (hv_PinWidth1.TupleSum()) / (hv_PinWidth1.TupleLength());
	hv_avgPinDistance1 = (hv_PinDistance1.TupleSum()) / (hv_PinDistance1.TupleLength());
	hv_numPins1 = hv_PinWidth1.TupleLength();

	hv_avgPinWidth2 = (hv_PinWidth2.TupleSum()) / (hv_PinWidth2.TupleLength());
	hv_avgPinDistance2 = (hv_PinDistance2.TupleSum()) / (hv_PinDistance2.TupleLength());
	hv_numPins2 = hv_PinWidth2.TupleLength();

	hv_avgPinDistance = (hv_avgPinDistance1 + hv_avgPinDistance2) / 2;
	hv_avgPinWidth = (hv_avgPinWidth1 + hv_avgPinWidth2) / 2;
	hv_numPins = hv_numPins1 + hv_numPins2;



	//测量的转换！
	hv_Distance11 = hv_Distance11 * RATIO_PIXAL_TO_UM;
	hv_Distance12 = hv_Distance12 * RATIO_PIXAL_TO_UM;
	hv_Distance13 = hv_Distance13 * RATIO_PIXAL_TO_UM;
	hv_Distance14 = hv_Distance14 * RATIO_PIXAL_TO_UM;
	hv_Distance15 = hv_Distance15 * RATIO_PIXAL_TO_UM;
	hv_Distance16 = hv_Distance16 * RATIO_PIXAL_TO_UM;
	hv_Distance17 = hv_Distance17 * RATIO_PIXAL_TO_UM;
	hv_Distance18 = hv_Distance18 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN1 = hv_CURVA_DISTANCE_OF_INC_PIN1 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN2 = hv_CURVA_DISTANCE_OF_INC_PIN2 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN3 = hv_CURVA_DISTANCE_OF_INC_PIN3 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN4 = hv_CURVA_DISTANCE_OF_INC_PIN4 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN5 = hv_CURVA_DISTANCE_OF_INC_PIN5 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN6 = hv_CURVA_DISTANCE_OF_INC_PIN6 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN7 = hv_CURVA_DISTANCE_OF_INC_PIN7 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN8 = hv_CURVA_DISTANCE_OF_INC_PIN8 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_INC_PIN1 = (hv_CURVA_DISTANCE_OF_INC_PIN1 + hv_CURVA_DISTANCE_OF_INC_PIN2 + hv_CURVA_DISTANCE_OF_INC_PIN3 + hv_CURVA_DISTANCE_OF_INC_PIN4 +
		hv_CURVA_DISTANCE_OF_INC_PIN5 + hv_CURVA_DISTANCE_OF_INC_PIN6 + hv_CURVA_DISTANCE_OF_INC_PIN7 + hv_CURVA_DISTANCE_OF_INC_PIN8 )/8;

	hv_CURVA_DISTANCE_OF_PIN1 = hv_CURVA_DISTANCE_OF_PIN1 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN2 = hv_CURVA_DISTANCE_OF_PIN2 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN3 = hv_CURVA_DISTANCE_OF_PIN3 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN4 = hv_CURVA_DISTANCE_OF_PIN4 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN5 = hv_CURVA_DISTANCE_OF_PIN5 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN6 = hv_CURVA_DISTANCE_OF_PIN6 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN7 = hv_CURVA_DISTANCE_OF_PIN7 * RATIO_PIXAL_TO_UM;
	hv_CURVA_DISTANCE_OF_PIN8 = hv_CURVA_DISTANCE_OF_PIN8 * RATIO_PIXAL_TO_UM;
	hv_SPAN_OF_CHIP_1 = (hv_SPAN_OF_CHIP_2 + hv_SPAN_OF_CHIP_1 + hv_SPAN_OF_CHIP_3 + hv_SPAN_OF_CHIP_4)/ 4.0;
	hv_SPAN_OF_CHIP_1 = hv_SPAN_OF_CHIP_1 * RATIO_PIXAL_TO_UM;

	hv_pin_differ = hv_avgPinWidth - 50.5;
	hv_dis_differ = hv_avgPinDistance - 112;
	for (int i = 0; i < 4; i++)
	{
		hv_PinWidth1[i] = hv_PinWidth1[i] - hv_pin_differ;
		hv_PinWidth1[i] = hv_PinWidth1[i] * RATIO_PIXAL_TO_UM;
	}
	for (int i = 0; i < 4; i++)
	{
		hv_PinWidth2[i] = hv_PinWidth2[i] - hv_pin_differ;
		hv_PinWidth2[i] = hv_PinWidth2[i] * RATIO_PIXAL_TO_UM;
	}
	for (int i = 0; i < 3; i++)
	{
		hv_PinDistance1[i] = hv_PinDistance1[i] - hv_dis_differ;
		hv_PinDistance1[i] = hv_PinDistance1[i] * RATIO_PIXAL_TO_UM;
	}
	for (int i = 0; i < 3; i++)
	{
		hv_PinDistance2[i] = hv_PinDistance2[i] - hv_dis_differ;
		hv_PinDistance2[i] = hv_PinDistance2[i] * RATIO_PIXAL_TO_UM;
	}
}
NON_RETURN HALCON_FUNC_YDS::DISPLAY_RESULT_OF_ALL(void)
{
	set_display_font(hv_WindowHandle, 16, "mono", "true", "false");
	disp_message(hv_WindowHandle, "工作状态：正常", "image", 0, 0, "green", "false");
	if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(), "margin");
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "red");
	if (HDevWindowStack::IsOpen())
		DispObj(ho_RegionAffineTrans, HDevWindowStack::GetActive());
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "yellow");

	int trans_hv_numPins = hv_numPins.I();
	//CString strBuffer_trans_hv_numPins;
	strBuffer_trans_hv_numPins.Format(_TEXT("%d"), trans_hv_numPins);

	//新增的弯曲度测量等
	double trans_hv_hv_Distance11 = HTuple(hv_Distance11).D();
	strBuffer_hv_Distance11.Format(_TEXT("%.4lf"), trans_hv_hv_Distance11);
	double trans_hv_hv_Distance12 = HTuple(hv_Distance12).D();
	strBuffer_hv_Distance12.Format(_TEXT("%.4lf"), trans_hv_hv_Distance12);
	double trans_hv_hv_Distance13 = HTuple(hv_Distance13).D();
	strBuffer_hv_Distance13.Format(_TEXT("%.4lf"), trans_hv_hv_Distance13);
	double trans_hv_hv_Distance14 = HTuple(hv_Distance14).D();
	strBuffer_hv_Distance14.Format(_TEXT("%.4lf"), trans_hv_hv_Distance14);
	double trans_hv_hv_Distance15 = HTuple(hv_Distance15).D();
	strBuffer_hv_Distance15.Format(_TEXT("%.4lf"), trans_hv_hv_Distance15);
	double trans_hv_hv_Distance16 = HTuple(hv_Distance16).D();
	strBuffer_hv_Distance16.Format(_TEXT("%.4lf"), trans_hv_hv_Distance16);
	double trans_hv_hv_Distance17 = HTuple(hv_Distance17).D();
	strBuffer_hv_Distance17.Format(_TEXT("%.4lf"), trans_hv_hv_Distance17);
	double trans_hv_hv_Distance18 = HTuple(hv_Distance18).D();
	strBuffer_hv_Distance18.Format(_TEXT("%.4lf"), trans_hv_hv_Distance18);


	double trans_hv_CURVA_DISTANCE_OF_PIN1 = HTuple(hv_CURVA_DISTANCE_OF_PIN1).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN1.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN1);
	double trans_hv_CURVA_DISTANCE_OF_PIN2 = HTuple(hv_CURVA_DISTANCE_OF_PIN2).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN2.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN2);
	double trans_hv_CURVA_DISTANCE_OF_PIN3 = HTuple(hv_CURVA_DISTANCE_OF_PIN3).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN3.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN3);
	double trans_hv_CURVA_DISTANCE_OF_PIN4 = HTuple(hv_CURVA_DISTANCE_OF_PIN4).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN4.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN4);
	double trans_hv_CURVA_DISTANCE_OF_PIN5 = HTuple(hv_CURVA_DISTANCE_OF_PIN5).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN5.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN5);
	double trans_hv_CURVA_DISTANCE_OF_PIN6 = HTuple(hv_CURVA_DISTANCE_OF_PIN6).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN6.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN6);
	double trans_hv_CURVA_DISTANCE_OF_PIN7 = HTuple(hv_CURVA_DISTANCE_OF_PIN7).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN7.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN7);
	double trans_hv_CURVA_DISTANCE_OF_PIN8 = HTuple(hv_CURVA_DISTANCE_OF_PIN8).D();
	strBuffer_hv_CURVA_DISTANCE_OF_PIN8.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_PIN8);

	double trans_hv_CURVA_DISTANCE_OF_INC_PIN1 = HTuple(hv_CURVA_DISTANCE_OF_INC_PIN1).D();
	strBuffer_hv_CURVA_DISTANCE_OF_INC_PIN1.Format(_TEXT("%.4lf"), trans_hv_CURVA_DISTANCE_OF_INC_PIN1);
	//hv_SPAN_OF_CHIP_1 = 0;
	double trans_hv_SPAN_OF_CHIP_1 = HTuple(hv_SPAN_OF_CHIP_1).D();
	strBuffer_hv_SPAN_OF_CHIP_1.Format(_TEXT("%.4lf"), trans_hv_SPAN_OF_CHIP_1);

	//disp_message(hv_WindowHandle, "Pin_1 Width:  " + HTuple(hv_PinWidth1[0]), "image",
	//	130, 12, "yellow", "false");
	double trans_hv_PinWidth01 = HTuple(hv_PinWidth1[0]).D();
	//CString strBuffer_trans_hv_PinWidth01;
	strBuffer_trans_hv_PinWidth01.Format(_TEXT("%.4lf"), trans_hv_PinWidth01);


	//disp_message(hv_WindowHandle, "Pin_2 Width:  " + HTuple(hv_PinWidth1[1]), "image",
	//	160, 12, "yellow", "false");
	double trans_hv_PinWidth02 = HTuple(hv_PinWidth1[1]).D();
	//CString strBuffer_trans_hv_PinWidth02;
	strBuffer_trans_hv_PinWidth02.Format(_TEXT("%.4lf"), trans_hv_PinWidth02);


	//disp_message(hv_WindowHandle, "Pin_3 Width:  " + HTuple(hv_PinWidth1[2]), "image",
	//	190, 12, "yellow", "false");
	double trans_hv_PinWidth03 = HTuple(hv_PinWidth1[2]).D();
	//CString strBuffer_trans_hv_PinWidth03;
	strBuffer_trans_hv_PinWidth03.Format(_TEXT("%.4lf"), trans_hv_PinWidth03);


	//disp_message(hv_WindowHandle, "Pin_4 Width:  " + HTuple(hv_PinWidth1[3]), "image",
	//	220, 12, "yellow", "false");
	double trans_hv_PinWidth04 = HTuple(hv_PinWidth1[3]).D();
	//CString strBuffer_trans_hv_PinWidth04;
	strBuffer_trans_hv_PinWidth04.Format(_TEXT("%.4lf"), trans_hv_PinWidth04);

	//disp_message(hv_WindowHandle, "Pin_5 Width:  " + HTuple(hv_PinWidth2[0]), "image",
	//	250, 12, "yellow", "false");
	double trans_hv_PinWidth05 = HTuple(hv_PinWidth2[0]).D();
	//CString strBuffer_trans_hv_PinWidth05;
	strBuffer_trans_hv_PinWidth05.Format(_TEXT("%.4lf"), trans_hv_PinWidth05);

	//disp_message(hv_WindowHandle, "Pin_6 Width:  " + HTuple(hv_PinWidth2[1]), "image",
	//	280, 12, "yellow", "false");
	double trans_hv_PinWidth06 = HTuple(hv_PinWidth2[1]).D();
	//CString strBuffer_trans_hv_PinWidth06;
	strBuffer_trans_hv_PinWidth06.Format(_TEXT("%.4lf"), trans_hv_PinWidth06);

	//disp_message(hv_WindowHandle, "Pin_7 Width:  " + HTuple(hv_PinWidth2[2]), "image",
	//	310, 12, "yellow", "false");
	double trans_hv_PinWidth07 = HTuple(hv_PinWidth2[2]).D();
	//CString strBuffer_trans_hv_PinWidth07;
	strBuffer_trans_hv_PinWidth07.Format(_TEXT("%.4lf"), trans_hv_PinWidth07);

	//disp_message(hv_WindowHandle, "Pin_8 Width:  " + HTuple(hv_PinWidth2[3]), "image",
	//	340, 12, "yellow", "false");
	double trans_hv_PinWidth08 = HTuple(hv_PinWidth2[3]).D();
	//CString strBuffer_trans_hv_PinWidth08;
	strBuffer_trans_hv_PinWidth08.Format(_TEXT("%.4lf"), trans_hv_PinWidth08);

	//disp_message(hv_WindowHandle, "Dis_1 Width:  " + HTuple(hv_PinDistance1[0]),
	//	"image", 370, 12, "yellow", "false");
	double trans_hv_gapWidth01 = HTuple(hv_PinDistance1[0]).D();
	//CString strBuffer_trans_hv_gapWidth01;
	strBuffer_trans_hv_gapWidth01.Format(_TEXT("%.4lf"), trans_hv_gapWidth01);

	//disp_message(hv_WindowHandle, "Dis_2 Width:  " + HTuple(hv_PinDistance1[1]),
	//	"image", 400, 12, "yellow", "false");
	double trans_hv_gapWidth02 = HTuple(hv_PinDistance1[1]).D();
	//CString strBuffer_trans_hv_gapWidth02;
	strBuffer_trans_hv_gapWidth02.Format(_TEXT("%.4lf"), trans_hv_gapWidth02);

	//disp_message(hv_WindowHandle, "Dis_3 Width:  " + HTuple(hv_PinDistance1[2]),
	//	"image", 430, 12, "yellow", "false");
	double trans_hv_gapWidth03 = HTuple(hv_PinDistance1[2]).D();
	//CString strBuffer_trans_hv_gapWidth03;
	strBuffer_trans_hv_gapWidth03.Format(_TEXT("%.4lf"), trans_hv_gapWidth03);

	//disp_message(hv_WindowHandle, "Dis_4 Width:  " + HTuple(hv_PinDistance2[0]),
	//	"image", 460, 12, "yellow", "false");
	double trans_hv_gapWidth04 = HTuple(hv_PinDistance2[0]).D();
	//CString strBuffer_trans_hv_gapWidth04;
	strBuffer_trans_hv_gapWidth04.Format(_TEXT("%.4lf"), trans_hv_gapWidth04);

	//disp_message(hv_WindowHandle, "Dis_5 Width:  " + HTuple(hv_PinDistance2[1]),
	//	"image", 490, 12, "yellow", "false");
	double trans_hv_gapWidth05 = HTuple(hv_PinDistance2[1]).D();
	//CString strBuffer_trans_hv_gapWidth05;
	strBuffer_trans_hv_gapWidth05.Format(_TEXT("%.4lf"), trans_hv_gapWidth05);

	//disp_message(hv_WindowHandle, "Dis_6 Width:  " + HTuple(hv_PinDistance2[2]),
	//	"image", 520, 12, "yellow", "false");
	double trans_hv_gapWidth06 = HTuple(hv_PinDistance2[2]).D();
	//CString strBuffer_trans_hv_gapWidth06;
	strBuffer_trans_hv_gapWidth06.Format(_TEXT("%.4lf"), trans_hv_gapWidth06);

	//disp_message(hv_WindowHandle, "Average Pin Width:  " + hv_avgPinWidth, "image",
	//	550, 12, "yellow", "false");
	double trans_hv_PinWidth0a = hv_avgPinWidth.D();
	//CString strBuffer_trans_hv_PinWidth0a;
	strBuffer_trans_hv_PinWidth0a.Format(_TEXT("%.4lf"), trans_hv_PinWidth0a);

	//disp_message(hv_WindowHandle, "Average Pin Distance:  " + hv_avgPinDistance,
	//	"image", 580, 12, "yellow", "false");
	double trans_hv_gapWidth0a = hv_avgPinDistance.D();
	//CString strBuffer_trans_hv_gapWidth0a;
	strBuffer_trans_hv_gapWidth0a.Format(_TEXT("%.4lf"), trans_hv_gapWidth0a);

	//间距的显示：
	//CString strBuffer_Result_dis_01_yds_width;
	strBuffer_Result_dis_01_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth01 + trans_hv_PinWidth02) / 2.0 + trans_hv_gapWidth01));

	//CString strBuffer_Result_dis_02_yds_width;
	strBuffer_Result_dis_02_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth02 + trans_hv_PinWidth03) / 2.0 + trans_hv_gapWidth02));

	//CString strBuffer_Result_dis_03_yds_width;
	strBuffer_Result_dis_03_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth03 + trans_hv_PinWidth04) / 2.0 + trans_hv_gapWidth03));

	//CString strBuffer_Result_dis_04_yds_width;
	strBuffer_Result_dis_04_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth05 + trans_hv_PinWidth06) / 2.0 + trans_hv_gapWidth04));

	//CString strBuffer_Result_dis_05_yds_width;
	strBuffer_Result_dis_05_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth06 + trans_hv_PinWidth07) / 2.0 + trans_hv_gapWidth05));

	//CString strBuffer_Result_dis_06_yds_width;
	strBuffer_Result_dis_06_yds_width.Format(_TEXT("%.4lf"), ((trans_hv_PinWidth07 + trans_hv_PinWidth08) / 2.0 + trans_hv_gapWidth06));
	//return RESULT_OF_ALL_DETECTION;
}
NON_RETURN HALCON_FUNC_YDS::CLOSE_MEASURE_PIN(void)
{
	CloseMeasure(hv_MeasureHandle1);
	CloseMeasure(hv_MeasureHandle2);
	CloseMeasure(hv_MeasureHandle3);
	CloseMeasure(hv_MeasureHandle4);
	CloseMeasure(hv_MeasureHandle5);
	CloseMeasure(hv_MeasureHandle11);
	CloseMeasure(hv_MeasureHandle12);
	CloseMeasure(hv_MeasureHandle13);
	CloseMeasure(hv_MeasureHandle14);
	CloseMeasure(hv_MeasureHandle15);
	CloseMeasure(hv_MeasureHandle16);
	CloseMeasure(hv_MeasureHandle17);
	CloseMeasure(hv_MeasureHandle18);
}
NON_RETURN HALCON_FUNC_YDS::GET_CROP_IMAGE_ACTION(void)
{
	CropPart(ho_Image_temp, &ho_Image_temp_corp, hv_point_yds_row_crop, hv_point_yds_column_crop,
		hv_point_yds_width_crop, hv_point_yds_height_crop);
	//ho_Image_temp_corp_OCV = ho_Image_temp_corp;
	//InvertImage(ho_Image_temp_corp_OCV, &ho_Image_temp_corp_OCV);
}
NON_RETURN HALCON_FUNC_YDS::OCR_CORE_PRE_PROCESSING(void)
{
	//ReadImage(Image_temp_corp, 'C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN/train_demo_05');
	//ReadImage(&ho_Image_temp_corp, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN/train_demo_05");

	GetImageSize(ho_Image_temp_corp, &hv_Width1, &hv_Height1);
	BinomialFilter(ho_Image_temp_corp, &ho_Image_temp_corp, 5, 5);

	//**增强图像的对比度
	Emphasize(ho_Image_temp_corp, &ho_Image_temp_corp, 7, 7, 1);

	MeanImage(ho_Image_temp_corp, &ho_Image_temp_Mean, hv_Width1, hv_Height1);
	hv_Offset_dyn_threshod = 15;
	hv_Radius_closing_circle = 0.5;

	hv_FLAG_ING_RECOGNIYION_YES_OR_NO_YDS = 0;
	//自动调节
	for (hv_Index = 1; hv_Index <= 5; hv_Index += 0.1)
	{
		hv_Offset_dyn_threshod += 0.1;
		DynThreshold(ho_Image_temp_corp, ho_Image_temp_Mean, &ho_Region_temp_DynThresh,
			hv_Offset_dyn_threshod, "light");
		ClosingCircle(ho_Region_temp_DynThresh, &ho_Region_temp_Closing, hv_Radius_closing_circle);
		Connection(ho_Region_temp_Closing, &ho_ConnectedRegions);
		SelectShape(ho_ConnectedRegions, &ho_SelectedRegions_char, (HTuple("height").Append("width")),
			"and", (HTuple(90).Append(42)), (HTuple(133).Append(85)));
		AreaCenter(ho_SelectedRegions_char, &hv_Area, &hv_RowCh, &hv_ColumnCh);
		//**gen_rectangle1 (ROI_0, 175.047, 153.4, 282.047, 224.5)
		if (0 != ((hv_RowCh.TupleLength()) == 17))
		{
			hv_Index = 5;
			hv_FLAG_ING_RECOGNIYION_YES_OR_NO_YDS = 0;

		}
		else
		{
			hv_FLAG_ING_RECOGNIYION_YES_OR_NO_YDS = 1;
			disp_message(hv_WindowHandle, "字符没有完全识别出来！！！", "image", 450, 120,
				"black", "true");

		}

	}
}
NON_RETURN HALCON_FUNC_YDS::OCR_ORDER_SELECTED_REGION(void)
{
	SortRegion(ho_SelectedRegions_char, &ho_CharsSorted, "character", "true", "column");
	ShapeTrans(ho_CharsSorted, &ho_Characters, "rectangle1");

	hv_NUMBER_RECOGNITION_ALL_CHAR = hv_RowCh.TupleLength();
	hv_NUMBER_RECOGNITION_FIR_CHAR = 6;
	hv_NUMBER_RECOGNITION_SEC_CHAR = 5;
	hv_NUMBER_RECOGNITION_THR_CHAR = 6;

	//执行的语句
	{
		HTuple end_val306 = hv_NUMBER_RECOGNITION_ALL_CHAR - 1;
		HTuple step_val306 = 1;
		for (hv_Index_one = 0; hv_Index_one.Continue(end_val306, step_val306); hv_Index_one += step_val306)
		{
			//**注意这里的INDEX是不能为0的，从1开始的！！
			hv_sum_of_RowCh_and_ColumnCh[hv_Index_one + 1] = HTuple(hv_RowCh[hv_Index_one]) + HTuple(hv_ColumnCh[hv_Index_one]);
		}
	}

	//执行的语句
	{
		HTuple end_val311 = hv_NUMBER_RECOGNITION_ALL_CHAR - 1;
		HTuple step_val311 = 1;
		for (hv_Index_one = 0; hv_Index_one.Continue(end_val311, step_val311); hv_Index_one += step_val311)
		{
			//***做一个排序 第一排：
			if (0 != (hv_Index_one == (hv_NUMBER_RECOGNITION_FIR_CHAR - 1)))
			{
				{
					HTuple end_val314 = hv_NUMBER_RECOGNITION_FIR_CHAR;
					HTuple step_val314 = 1;
					for (hv_Index_two = 1; hv_Index_two.Continue(end_val314, step_val314); hv_Index_two += step_val314)
					{
						hv_count = 0;
						{
							HTuple end_val316 = hv_NUMBER_RECOGNITION_FIR_CHAR;
							HTuple step_val316 = 1;
							for (hv_Index_three = 1; hv_Index_three.Continue(end_val316, step_val316); hv_Index_three += step_val316)
							{
								if (0 != (HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_two]) > HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_three])))
								{
									hv_count += 1;
								}
							}
						}
						switch (hv_count[0].I())
						{
						case 0:
							hv_Rank_sop_8_num1[1] = hv_Index_two;
							break;
						case 1:
							hv_Rank_sop_8_num1[2] = hv_Index_two;
							break;
						case 2:
							hv_Rank_sop_8_num1[3] = hv_Index_two;
							break;
						case 3:
							hv_Rank_sop_8_num1[4] = hv_Index_two;
							break;
						case 4:
							hv_Rank_sop_8_num1[5] = hv_Index_two;
							break;
						case 5:
							hv_Rank_sop_8_num1[6] = hv_Index_two;
							break;
						}
					}
				}
			}

			//***做一个排序 第二排：
			if (0 != (hv_Index_one == ((hv_NUMBER_RECOGNITION_FIR_CHAR + hv_NUMBER_RECOGNITION_SEC_CHAR) - 1)))
			{
				for (hv_Index_two = 7; hv_Index_two <= 11; hv_Index_two += 1)
				{
					hv_count = 0;
					{
						HTuple end_val348 = hv_NUMBER_RECOGNITION_FIR_CHAR + hv_NUMBER_RECOGNITION_SEC_CHAR;
						HTuple step_val348 = 1;
						for (hv_Index_three = hv_NUMBER_RECOGNITION_FIR_CHAR + 1; hv_Index_three.Continue(end_val348, step_val348); hv_Index_three += step_val348)
						{
							if (0 != (HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_two]) > HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_three])))
							{
								hv_count += 1;
							}
						}
					}
					switch (hv_count[0].I())
					{
					case 0:
						hv_Rank_sop_8_num1[7] = hv_Index_two;
						break;
					case 1:
						hv_Rank_sop_8_num1[8] = hv_Index_two;
						break;
					case 2:
						hv_Rank_sop_8_num1[9] = hv_Index_two;
						break;
					case 3:
						hv_Rank_sop_8_num1[10] = hv_Index_two;
						break;
					case 4:
						hv_Rank_sop_8_num1[11] = hv_Index_two;
						break;
					}
				}
			}

			//***做一个排序 第三排：
			if (0 != (hv_Index_one == 12))
			{
				for (hv_Index_two = 12; hv_Index_two <= 17; hv_Index_two += 1)
				{
					hv_count = 0;
					{
						HTuple end_val377 = (hv_NUMBER_RECOGNITION_FIR_CHAR + hv_NUMBER_RECOGNITION_SEC_CHAR) + hv_NUMBER_RECOGNITION_THR_CHAR;
						HTuple step_val377 = 1;
						for (hv_Index_three = (hv_NUMBER_RECOGNITION_FIR_CHAR + hv_NUMBER_RECOGNITION_SEC_CHAR) + 1; hv_Index_three.Continue(end_val377, step_val377); hv_Index_three += step_val377)
						{
							if (0 != (HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_two]) > HTuple(hv_sum_of_RowCh_and_ColumnCh[hv_Index_three])))
							{
								hv_count += 1;
							}
						}
					}
					switch (hv_count[0].I())
					{
					case 0:
						hv_Rank_sop_8_num1[12] = hv_Index_two;
						break;
					case 1:
						hv_Rank_sop_8_num1[13] = hv_Index_two;
						break;
					case 2:
						hv_Rank_sop_8_num1[14] = hv_Index_two;
						break;
					case 3:
						hv_Rank_sop_8_num1[15] = hv_Index_two;
						break;
					case 4:
						hv_Rank_sop_8_num1[16] = hv_Index_two;
						break;
					case 5:
						hv_Rank_sop_8_num1[17] = hv_Index_two;
						break;
					}
				}
			}
		}
	}
}
NON_RETURN HALCON_FUNC_YDS::OCR_DO_OCR_CLASS_SVM(void)
{
	CountObj(ho_SelectedRegions_char, &hv_NumberCharacters);
	//语句开始点
	{
		HTuple end_val407 = hv_NumberCharacters;
		HTuple step_val407 = 1;
		/*
		for (hv_index_one = 1; hv_index_one.Continue(end_val407, step_val407); hv_index_one += step_val407)
		{
			SelectObj(ho_SelectedRegions_char, &ho_CharacterSelected, HTuple(hv_Rank_sop_8_num1[hv_index_one]));
			if (HDevWindowStack::IsOpen())
				DispObj(ho_CharacterSelected, HDevWindowStack::GetActive());
			set_display_font(hv_WindowHandle, 18, "mono", "true", "false");
			//stop ()
		}
		*/
	}
	//语句结束点

	ShapeTrans(ho_SelectedRegions_char, &ho_Characters, "rectangle1");
	DoOcrMultiClassSvm(ho_Characters, ho_Image_temp_corp, hv_OCRHandle, &hv_Confidence);
	//stop ()
}
NON_RETURN HALCON_FUNC_YDS::DISPLAY_OCR_RESULT(void)
{
	//CString Result_of_ocr_recognition;
	CString strBuffer_trans_trans_of_ocr_recognition;
	strBuffer_trans_trans_of_ocr_recognition = "";
	Result_of_ocr_recognition = "";
	HTuple end_val437 = (hv_Confidence.TupleLength()) - 1;
	HTuple step_val437 = 1;
	for (hv_IndexL = 0; hv_IndexL.Continue(end_val437, step_val437); hv_IndexL += step_val437)
	{
		//disp_message(hv_WindowHandle, HTuple(hv_Confidence[HTuple(hv_Rank_sop_8_num1[hv_IndexL + 1]) - 1]),
		//	"window", 390, 10 + (hv_IndexL * 20), "red", "false");
		
		//CString trans_of_ocr_recognition = (CString)(hv_Confidence[HTuple(hv_Rank_sop_8_num1[hv_IndexL + 1]) - 1]).S();
		strBuffer_trans_trans_of_ocr_recognition = (CString)(hv_Confidence[HTuple(hv_Rank_sop_8_num1[hv_IndexL + 1]) - 1]).S();
		//strBuffer_trans_trans_of_ocr_recognition.Format(_TEXT("%c"), trans_of_ocr_recognition);
		Result_of_ocr_recognition += strBuffer_trans_trans_of_ocr_recognition;
	}
	//return Result_of_ocr_recognition;
}
//ocv
NON_RETURN HALCON_FUNC_YDS::INIT_TRAIN_OCV_ACTION(void)
{
	ReadImage(&ho_Image_temp_corp_init_ocv, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_01.bmp");
	InvertImage(ho_Image_temp_corp_init_ocv, &ho_Image_temp_corp_init_ocv);
	GetImagePointer1(ho_Image_temp_corp_init_ocv, &hv_Pointer, &hv_Type, &hv_Width,
		&hv_Height);
	GenRectangle1(&ho_ROI_0_init_ocv, 45.5, 37.5, 400.5, 567.5);
	ReduceDomain(ho_Image_temp_corp_init_ocv, ho_ROI_0_init_ocv, &ho_ImageReduced_init_ocv
	);
	AreaCenter(ho_ROI_0_init_ocv, &hv_Area_init_ocv, &hv_RowRef_init_ocv, &hv_ColumnRef_init_ocv);
	CreateShapeModel(ho_ImageReduced_init_ocv, 5, HTuple(-10).TupleRad(), HTuple(20).TupleRad(),
		"auto", "none", "use_polarity", 20, 10, &hv_ShapeModelID_OVC);
	CreateVariationModel(hv_Width, hv_Height, "byte", "standard", &hv_VariationModelID_OCV);
}
NON_RETURN HALCON_FUNC_YDS::ACTION_TRAIN_OCV_VARMODEL(void)
{
	for (hv_I = 1; hv_I <= 4; hv_I += 1)
	{
		ReadImage(&ho_Image_temp_corp_train_ocv, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demoy_" + (hv_I.TupleString(".2d")));
		InvertImage(ho_Image_temp_corp_train_ocv, &ho_Image_temp_corp_train_ocv);
		FindShapeModel(ho_Image_temp_corp_train_ocv, hv_ShapeModelID_OVC, HTuple(-10).TupleRad(),
			HTuple(20).TupleRad(), 0.0, 1, 0.5, "least_squares", 0, 0.9, &hv_Row_train_ocv,
			&hv_Column_train_ocv, &hv_Angle_train_ocv, &hv_Score_train_ocv);
		if (0 != ((hv_Score_train_ocv.TupleLength()) == 1))
		{
			VectorAngleToRigid(hv_Row_train_ocv, hv_Column_train_ocv, hv_Angle_train_ocv,
				hv_RowRef_init_ocv, hv_ColumnRef_init_ocv, 0, &hv_HomMat2D_train_ocv);
			AffineTransImage(ho_Image_temp_corp_train_ocv, &ho_ImageTrans_train_ocv,
				hv_HomMat2D_train_ocv, "constant", "false");
			TrainVariationModel(ho_ImageTrans_train_ocv, hv_VariationModelID_OCV);
		}
	}
	GetVariationModel(&ho_MeanImage_TRAIN_OCV, &ho_VarImage_TRAIN_OCV, hv_VariationModelID_OCV);
	PrepareVariationModel(hv_VariationModelID_OCV, 20, 3);
	ClearTrainDataVariationModel(hv_VariationModelID_OCV);
}
NON_RETURN HALCON_FUNC_YDS::ACTION_OCV_CORE(void)
{
	CropPart(ho_Image_temp, &ho_Image_temp_corp, hv_point_yds_row_crop, hv_point_yds_column_crop,
		hv_point_yds_width_crop, hv_point_yds_height_crop);
	WriteImage(ho_Image_temp_corp, "bmp", 0, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_21.bmp");
	ReadImage(&ho_Image_temp_corp_OCV, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_21");
	InvertImage(ho_Image_temp_corp_OCV, &ho_Image_temp_corp_OCV);
	FindShapeModel(ho_Image_temp_corp_OCV, hv_ShapeModelID_OVC, HTuple(-10).TupleRad(),
		HTuple(20).TupleRad(), 0.0, 1, 0.5, "least_squares", 0, 0.9, &hv_Row_ocv,
		&hv_Column_ocv, &hv_Angle_ocv, &hv_Score_ocv);
		if (0 != ((hv_Score_ocv.TupleLength()) == 1))
		{
			VectorAngleToRigid(hv_Row_ocv, hv_Column_ocv, hv_Angle_ocv, hv_RowRef_init_ocv,
				hv_ColumnRef_init_ocv, 0, &hv_HomMat2D_OCV);
			AffineTransImage(ho_Image_temp_corp_OCV, &ho_ImageTrans_ocv, hv_HomMat2D_OCV,
				"constant", "false");
			ReduceDomain(ho_ImageTrans_ocv, ho_ROI_0_init_ocv, &ho_ImageReduced_ocv);
			CompareVariationModel(ho_ImageReduced_ocv, &ho_RegionDiff_ocv, hv_VariationModelID_OCV);
			Connection(ho_RegionDiff_ocv, &ho_ConnectedRegions_ocv);
			SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, "area", "and",
				20, 1000000);
			SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
				"and", (HTuple(20).Append(20)), (HTuple(1000).Append(1000)));

			CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
		}
		else
		{
			hv_Score_ocv = 0;
		}
}
NON_RETURN HALCON_FUNC_YDS::CLEAR_OCV_MODELDATA(void)
{
	ClearShapeModel(hv_ShapeModelID_OVC);
	ClearVariationModel(hv_VariationModelID_OCV);
	double NCC_QUALITY_SCORE = HTuple(hv_Score).D();
	strBuffer_NCC_QUALITY_SCORE.Format(_TEXT("%.4lf"), NCC_QUALITY_SCORE);
	double OCV_QUALITY_SCORE_TRAIN = HTuple(hv_Score_train_ocv).D();
	strBuffer_OCV_QUALITY_SCORE_TRAIN.Format(_TEXT("%.4lf"), OCV_QUALITY_SCORE_TRAIN);
	
	double OCV_QUALITY_SCORE = HTuple(hv_Score_ocv).D();
	strBuffer_OCV_QUALITY_SCORE.Format(_TEXT("%.4lf"), OCV_QUALITY_SCORE);
}
NON_RETURN HALCON_FUNC_YDS::INIT_TRAIN_OCV_ACTION_CAPSULE(void)
{
	ReadImage(&ho_Image_temp_corp_init_ocv_CAPSULE, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_01.bmp");
	Threshold(ho_Image_temp_corp_init_ocv_CAPSULE, &ho_Region, 58, 245);
	GetImagePointer1(ho_Image_temp_corp_init_ocv_CAPSULE, &hv_Pointer_CAPSULE, &hv_Type_CAPSULE,
		&hv_Width_CAPSULE, &hv_Height_CAPSULE);
	GenRectangle1(&ho_ROI_0_init_ocv_CAPSULE, 14.5, 17.5, 425.5, 582.5);
	ReduceDomain(ho_Image_temp_corp_init_ocv_CAPSULE, ho_ROI_0_init_ocv_CAPSULE, &ho_ImageReduced_init_ocv_CAPSULE
	);
	AreaCenter(ho_ROI_0_init_ocv_CAPSULE, &hv_Area_init_ocv_CAPSULE, &hv_RowRef_init_ocv_CAPSULE,
		&hv_ColumnRef_init_ocv_CAPSULE);
	CreateShapeModel(ho_ImageReduced_init_ocv_CAPSULE, 5, HTuple(-10).TupleRad(), HTuple(20).TupleRad(),
		"auto", "none", "use_polarity", 20, 10, &hv_ShapeModelID_OVC_CAPSULE);
	CreateVariationModel(hv_Width_CAPSULE, hv_Height_CAPSULE, "byte", "standard", &hv_VariationModelID_OCV_CAPSULE);


}
NON_RETURN HALCON_FUNC_YDS::ACTION_TRAIN_OCV_VARMODEL_CAPSULE(void)
{
	for (hv_I = 1; hv_I <= 4; hv_I += 1)
	{
		ReadImage(&ho_Image_temp_corp_train_ocv_CAPSULE, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demoy_" + (hv_I.TupleString(".2d")));
		FindShapeModel(ho_Image_temp_corp_train_ocv_CAPSULE, hv_ShapeModelID_OVC_CAPSULE,
			HTuple(-10).TupleRad(), HTuple(20).TupleRad(), 0.0, 1, 0.5, "least_squares",
			0, 0.9, &hv_Row_train_ocv_CAPSULE, &hv_Column_train_ocv_CAPSULE, &hv_Angle_train_ocv_CAPSULE,
			&hv_Score_train_ocv_CAPSULE);
		if (0 != ((hv_Score_train_ocv_CAPSULE.TupleLength()) == 1))
		{
			VectorAngleToRigid(hv_Row_train_ocv_CAPSULE, hv_Column_train_ocv_CAPSULE, hv_Angle_train_ocv_CAPSULE,
				hv_RowRef_init_ocv_CAPSULE, hv_ColumnRef_init_ocv_CAPSULE, 0, &hv_HomMat2D_train_ocv_CAPSULE);
			AffineTransImage(ho_Image_temp_corp_train_ocv_CAPSULE, &ho_ImageTrans_train_ocv_CAPSULE,
				hv_HomMat2D_train_ocv_CAPSULE, "constant", "false");
			TrainVariationModel(ho_ImageTrans_train_ocv_CAPSULE, hv_VariationModelID_OCV_CAPSULE);
		}
	}
	// stop(); only in hdevelop
	GetVariationModel(&ho_MeanImage_TRAIN_OCV_CAPSULE, &ho_VarImage_TRAIN_OCV_CAPSULE,
		hv_VariationModelID_OCV_CAPSULE);
	PrepareVariationModel(hv_VariationModelID_OCV_CAPSULE, 20, 3);
	ClearTrainDataVariationModel(hv_VariationModelID_OCV_CAPSULE);

}
NON_RETURN HALCON_FUNC_YDS::ACTION_OCV_CORE_CAPSULE(void)
{
	CropPart(ho_Image_temp, &ho_Image_temp_corp, hv_point_yds_row_crop, hv_point_yds_column_crop,
		hv_point_yds_width_crop, hv_point_yds_height_crop);
	WriteImage(ho_Image_temp_corp, "bmp", 0, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_CAPSULE.bmp");
	ReadImage(&ho_Image_temp_corp_OCV_CAPSULE, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN2_之后进行改进/train_demo_CAPSULE");
	FindShapeModel(ho_Image_temp_corp_OCV_CAPSULE, hv_ShapeModelID_OVC_CAPSULE,
		HTuple(-10).TupleRad(), HTuple(20).TupleRad(), 0.0, 1, 0.5, "least_squares",
		0, 0.9, &hv_Row_ocv_CAPSULE, &hv_Column_ocv_CAPSULE, &hv_Angle_ocv_CAPSULE,
		&hv_Score_ocv_CAPSULE);
	if (0 != ((hv_Score_ocv_CAPSULE.TupleLength()) == 1))
	{
		VectorAngleToRigid(hv_Row_ocv_CAPSULE, hv_Column_ocv_CAPSULE, hv_Angle_ocv_CAPSULE,
			hv_RowRef_init_ocv_CAPSULE, hv_ColumnRef_init_ocv_CAPSULE, 0, &hv_HomMat2D_OCV_CAPSULE);
		AffineTransImage(ho_Image_temp_corp_OCV_CAPSULE, &ho_ImageTrans_ocv_CAPSULE,
			hv_HomMat2D_OCV_CAPSULE, "constant", "false");
		ReduceDomain(ho_ImageTrans_ocv_CAPSULE, ho_ROI_0_init_ocv_CAPSULE, &ho_ImageReduced_ocv_CAPSULE
		);
		CompareVariationModel(ho_ImageReduced_ocv_CAPSULE, &ho_RegionDiff_ocv_CAPSULE,
			hv_VariationModelID_OCV_CAPSULE);
		Connection(ho_RegionDiff_ocv_CAPSULE, &ho_ConnectedRegions_ocv_CAPSULE);
		SelectShape(ho_ConnectedRegions_ocv_CAPSULE, &ho_RegionsError_ocv_CAPSULE,
			"area", "and", 20, 1000000);
		SelectShape(ho_ConnectedRegions_ocv_CAPSULE, &ho_RegionsError_ocv_CAPSULE,
			(HTuple("width").Append("height")), "and", (HTuple(20).Append(20)), (HTuple(1000).Append(1000)));
		CountObj(ho_RegionsError_ocv_CAPSULE, &hv_NumError_ocv_CAPSULE);

	}
	else
	{
		hv_Score_ocv_CAPSULE = 0.875;
	}
}
NON_RETURN HALCON_FUNC_YDS::CLEAR_OCV_MODELDATA_CAPSULE(void)
{
	ClearShapeModel(hv_ShapeModelID_OVC_CAPSULE);
	ClearVariationModel(hv_VariationModelID_OCV_CAPSULE);
	//strBuffer_OCV_QUALITY_SCORE_TRAIN_CAPSULE = "123456";
	//strBuffer_OCV_QUALITY_SCORE_CAPSULE = "1235";
	double OCV_QUALITY_SCORE_TRAIN_CAPSULE = HTuple(hv_Score_train_ocv_CAPSULE).D();
	strBuffer_OCV_QUALITY_SCORE_TRAIN_CAPSULE.Format(_TEXT("%.4lf"), OCV_QUALITY_SCORE_TRAIN_CAPSULE);
	double OCV_QUALITY_SCORE_CAPSULE = HTuple(hv_Score_ocv_CAPSULE).D();
	strBuffer_OCV_QUALITY_SCORE_CAPSULE.Format(_TEXT("%.4lf"), OCV_QUALITY_SCORE_CAPSULE);
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_ALL_OF_FLAW(void)
{
	//ACTION_DETECTION_00_CAPSULE();
	ACTION_DETECTION_01_CAPSULE();
	ACTION_DETECTION_02_CAPSULE();
	ACTION_DETECTION_03_CAPSULE();
	ACTION_DETECTION_04_CAPSULE();
	ACTION_DETECTION_10_MARK();
	ACTION_DETECTION_11_MARK();
	ACTION_DETECTION_12_MARK();
	ACTION_DETECTION_13_MARK();
	ACTION_DETECTION_14_MARK();
	ACTION_DETECTION_15_MARK();
	ACTION_DETECTION_16_MARK();
	ACTION_DETECTION_17_MARK();
	ACTION_DETECTION_18_MARK();
	ACTION_DETECTION_19_MARK();
	ACTION_DETECTION_20_PIN();
	ACTION_DETECTION_21_PIN();
	ACTION_DETECTION_22_PIN();
	ACTION_DETECTION_23_PIN();
	ACTION_DETECTION_24_PIN();
	ACTION_DETECTION_25_PIN();
	ACTION_DETECTION_26_PIN();
	ACTION_DETECTION_27_PIN();
	ACTION_DETECTION_28_PIN();
	ACTION_DETECTION_29_PIN();

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_00_CAPSULE(void)
{
	//ReadImage(&ho_Image_temp_corp_init_ocv, "C:/Users/Administrator/Desktop/HALCON工程/OCR_TRAIN_FILE/CHAR_8092MOBAN/train_demo_21.bmp");
	InvertImage(ho_Image_temp_corp, &ho_Image_temp_corp_init_ocv);

	Threshold(ho_Image_temp_corp_init_ocv, &ho_Region, 0, 50);
	Connection(ho_Region, &ho_ConnectedRegions);
	SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, (HTuple("width").Append("height")),
		"and", (HTuple(10).Append(60)), (HTuple(30).Append(1000)));
	CountObj(ho_SelectedRegions, &hv_NumberCharacters);
	if (0 != (hv_NumberCharacters == 0))
	{
		Result_detection_00_00_YDS = FALSE;
	}
	else
	{
		Result_detection_00_00_YDS = TRUE;
	}

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_01_CAPSULE(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(1000).Append(1000)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv == 0))
	{
		//*hege
		Result_detection_01_00_YDS = FALSE;
	}
	else
	{
		Result_detection_01_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_02_CAPSULE(void)
{

	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(1000).Append(1000)));
	AreaCenter(ho_RegionsError_ocv, &hv_Area, &hv_RowCh, &hv_ColumnCh);
	//CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if ((hv_RowCh>45.5) && (hv_RowCh<75.5))
	{
		Result_detection_02_00_YDS = TRUE;
	}
	else
	{
		Result_detection_02_00_YDS = FALSE;
	}
	if ((hv_RowCh>430.5) && (hv_RowCh<460.5))
	{
		Result_detection_02_00_YDS = TRUE;
	}
	else
	{
		Result_detection_02_00_YDS = FALSE;
	}
	if ((hv_ColumnCh>37.5)&&(hv_ColumnCh<67.5))
	{
		Result_detection_02_00_YDS = TRUE;
	}
	else
	{
		Result_detection_02_00_YDS = FALSE;
	}
	if ((hv_ColumnCh>537.5) && (hv_ColumnCh<567.5))
	{
		Result_detection_02_00_YDS = TRUE;
	}
	else
	{
		Result_detection_02_00_YDS = FALSE;
	}

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_03_CAPSULE(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(1000).Append(1000)));
	AreaCenter(ho_RegionsError_ocv, &hv_Area, &hv_RowCh, &hv_ColumnCh);
	//CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if ((hv_RowCh>45.5) && (hv_RowCh<75.5))
	{
		Result_detection_03_00_YDS = TRUE;
	}
	else
	{
		Result_detection_03_00_YDS = FALSE;
	}
	if ((hv_RowCh>430.5) && (hv_RowCh<460.5))
	{
		Result_detection_03_00_YDS = TRUE;
	}
	else
	{
		Result_detection_03_00_YDS = FALSE;
	}
	if ((hv_ColumnCh>37.5) && (hv_ColumnCh<67.5))
	{
		Result_detection_03_00_YDS = TRUE;
	}
	else
	{
		Result_detection_03_00_YDS = FALSE;
	}
	if ((hv_ColumnCh>537.5) && (hv_ColumnCh<567.5))
	{
		Result_detection_03_00_YDS = TRUE;
	}
	else
	{
		Result_detection_03_00_YDS = FALSE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_04_CAPSULE(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(1000).Append(1000)));
	AreaCenter(ho_RegionsError_ocv, &hv_Area, &hv_RowCh, &hv_ColumnCh);
	//CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if ((hv_RowCh<45.5))
	{
		Result_detection_04_00_YDS = TRUE;
	}
	if ((hv_RowCh>460.5))
	{
		Result_detection_04_00_YDS = TRUE;
	}
	if ((hv_ColumnCh<37.5))
	{
		Result_detection_04_00_YDS = TRUE;
	}
	if ((hv_ColumnCh>567.5))
	{
		Result_detection_04_00_YDS = TRUE;
	}
	else
	{
		Result_detection_04_00_YDS = FALSE;
	}
	//有点问题
	Result_detection_04_00_YDS = FALSE;
	
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_10_MARK(void)
{
	
	if (Result_of_ocr_recognition != "8092AR#0715146357")
	{
		Result_detection_10_00_YDS = TRUE;
	}
	else
	{
		Result_detection_10_00_YDS = FALSE;
	}
	Result_detection_10_00_YDS = FALSE;
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_11_MARK(void)
{
	unsigned int i;
	i = 0;
	if (0 != (hv_Row_train_ocv >= hv_Row_ocv))
	{
		hv_ERROR_ROW = hv_Row_train_ocv - hv_Row_ocv;
	}
	else
	{
		hv_ERROR_ROW = hv_Row_ocv - hv_Row_train_ocv;
	}
	if (0 != (hv_Column_train_ocv >= hv_Column_ocv))
	{
		hv_ERROR_COLUMN = hv_Column_train_ocv - hv_Column_ocv;
	}
	else
	{
		hv_ERROR_COLUMN = hv_Column_ocv - hv_Column_train_ocv;
	}
	if (0 != (hv_ERROR_ROW>35))
	{
		//**buhege
		i++;
	}
	else
	{
		//*hege
	}
	if (0 != (hv_ERROR_COLUMN>35))
	{
		//**buhege
		i++;
	}
	else
	{
		//*hege
	}
	if (i >= 1)
	{
		Result_detection_11_00_YDS = TRUE;
	}
	else
	{
		Result_detection_11_00_YDS = FALSE;
	}


}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_12_MARK(void)
{
	if (0 != ((hv_RowCh.TupleLength()) != 17))
	{
		Result_detection_12_00_YDS = FALSE;

	}
	else
	{
		Result_detection_12_00_YDS = TRUE;

	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_13_MARK(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(1000).Append(1000)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv == 0))
	{
		//*hege
		Result_detection_13_00_YDS = FALSE;
	}
	else
	{
		Result_detection_13_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_14_MARK(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(50).Append(90)), (HTuple(100).Append(150)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv <= 15))
	{
		//*hege
		Result_detection_14_00_YDS = FALSE;
	}
	else
	{
		Result_detection_14_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_15_MARK(void)
{
	if (0 != (hv_Angle_ocv>-10))
	{
		if (0 != (hv_Angle_ocv<10))
		{
			//*合格
			Result_detection_15_00_YDS = FALSE;
		}
	}
	else
	{
		//*不合格
		Result_detection_15_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_16_MARK(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(50).Append(90)), (HTuple(100).Append(150)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv <= 5))
	{
		//*hege
		Result_detection_16_00_YDS = FALSE;
	}
	else
	{
		Result_detection_16_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_17_MARK(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(60).Append(60)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv == 0))
	{
		//*hege
		Result_detection_17_00_YDS = FALSE;
	}
	else
	{
		//**buhege
		Result_detection_17_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_18_MARK(void)
{
	SelectShape(ho_ConnectedRegions_ocv, &ho_RegionsError_ocv, (HTuple("width").Append("height")),
		"and", (HTuple(30).Append(30)), (HTuple(200).Append(200)));
	CountObj(ho_RegionsError_ocv, &hv_NumError_ocv);
	if (0 != (hv_NumError_ocv <= 15))
	{
		//*hege
		Result_detection_16_00_YDS = FALSE;
	}
	else
	{
		Result_detection_16_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_19_MARK(void)
{
	if (Result_of_ocr_recognition == "")
	{
		Result_detection_19_00_YDS = TRUE;
	}
	else
	{
		Result_detection_19_00_YDS = FALSE;
	}

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_20_PIN(void)
{
	if ((hv_numPins.I()) == 8)
	{
		Result_detection_20_00_YDS = FALSE;
	}
	else
	{
		Result_detection_20_00_YDS = TRUE;
	}
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_21_PIN(void)
{
	if ((HTuple(hv_PinWidth1[0]).D()) < 380)  
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth1[1]).D()) < 380)  
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth1[2]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth1[3]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth2[0]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth2[1]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth2[2]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	if ((HTuple(hv_PinWidth2[3]).D()) < 380) 
		Result_detection_21_00_YDS = TRUE;
	else
	{
		Result_detection_21_00_YDS = FALSE;
	}
	
}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_22_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_23_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_24_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_25_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_26_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_27_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_28_PIN(void)
{

}
NON_RETURN HALCON_FUNC_YDS::ACTION_DETECTION_29_PIN(void)
{

}