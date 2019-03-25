#ifndef _XUIASSIST_H_
#define _XUIASSIST_H_

#include "XString.h"

extern const XString EMPTY_STRING;

#define XUI_FLOAT_NEAR_ZERO	0.0001F

#define XUI_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define XUI_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define XUI_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define XUI_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

enum XUIResolutionPolicy
{
	XUI_UNKNOWN,
	XUI_EXACTFIT,
	XUI_NOBORDER,
	XUI_SHOWALL,
	XUI_FIXEDHEIGHT,
	XUI_FIXEDWIDTH,
};

enum WidgetPriority
{
	XUI_PRIORITY_NORMAL = 0,
	XUI_PRIORITY_DIALOG = -128,
	XUI_PRIORITY_DIALOG_WIDGET = -129,
};

#define TYPESTRING_NODE			"Node"
#define TYPESTRING_WIDGET		"Widget"
#define TYPESTRING_SCENE		"Scene"
#define TYPESTRING_IMAGE		"Image"
#define TYPESTRING_LABEL		"Label"
#define TYPESTRING_BUTTON		"Button"
#define TYPESTRING_DIALOG		"Dialog"
#define TYPESTRING_EDITBOX		"EditBox"
#define TYPESTRING_PROGRESSBAR	"ProgressBar"
#define TYPESTRING_RICHTEXT		"RichText"
#define TYPESTRING_LAYOUT		"Layout"
#define TYPESTRING_RICHELEMENT "RichElement"
#define TYPESTRING_RICHELEMENT_TEXT "RichElementText"
#define TYPESTRING_RICHELEMENT_IMAGE "RichElementImage"
#define TYPESTRING_RICHELEMENT_CUSTOM "RichElementCustom"
#define TYPESTRING_RICHELEMENT_NEWLINE "RichElementNewLine"
#define TYPESTRING_SLIDER		"Slider"
#define TYPESTRING_CHECKBOX		"CheckBox"
#define TYPESTRING_SCROLLVIEW	"ScrollView"
#define TYPESTRING_LISTVIEW		"ListView"
#define TYPESTRING_PAGEVIEW		"PageView"
#define TYPESTRING_TREEVIEW		"TreeView"
#define TYPESTRING_RADIOBUTTON	"RadioButton"
#define TYPESTRING_RADIOBUTTONGROUP "RadioButtonGroup"
#define TYPESTRING_COMBOBOX		"ComboBox"
#define TYPESTRING_TABVIEW		"TabView"
#define TYPESTRING_IMAGEARRAY	"ImageArray"
#define TYPESTRING_GUIDEPAGE	"GuidePage"
#define TYPESTRING_GUIDEPAGEGROUP	"GuidePageGroup"
#define TYPESTRING_DYNAMICLISTVIEW	"DynamicListView"
#endif
