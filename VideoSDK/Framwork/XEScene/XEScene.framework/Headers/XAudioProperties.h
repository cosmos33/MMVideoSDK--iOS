#ifndef XAUDIO_PROPERTIES_H_
#define XAUDIO_PROPERTIES_H_

#include "XMath3D.h"

#include <list>
#include <vector>
#include <string>


class XFileBase;
namespace XAudio
{
	class XAudioStream;
	class XAudioProperties
	{
	public:
		enum Type
		{
			NONE,
			STRING,
			NUMBER,
			VECTOR2,
			VECTOR3,
			VECTOR4,
			MATRIX
		};
		
		static XAudioProperties* create(const char* url);
		
		~XAudioProperties();

		const char* getNextProperty();

		XAudioProperties* getNextNamespace();

		void rewind();
		
		XAudioProperties* getNamespace(const char* id, bool searchNames = false, bool recurse = true) const;

		const char* getNamespace() const;

		const char* getId() const;

		bool exists(const char* name) const;

		Type getType(const char* name = NULL) const;

		const char* getString(const char* name = NULL, const char* defaultValue = NULL) const;

		bool setString(const char* name, const char* value);

		bool getBool(const char* name = NULL, bool defaultValue = false) const;

		int getInt(const char* name = NULL) const;

		float getFloat(const char* name = NULL) const;

		long getLong(const char* name = NULL) const;

		bool getMatrix(const char* name, XMATRIX4* out) const;
				
		bool getVector2(const char* name, XVECTOR2* out) const;

		bool getVector3(const char* name, XVECTOR3* out) const;

		bool getVector4(const char* name, XVECTOR4* out) const;

		bool getQuaternionFromAxisAngle(const char* name, XQUATERNION* out) const;

		bool getColor(const char* name, XVECTOR3* out) const;

		bool getColor(const char* name, XVECTOR4* out) const;

		bool getPath(const char* name, std::string* path) const;
				
		const char* getVariable(const char* name, const char* defaultValue = NULL) const;

		void setVariable(const char* name, const char* value);

		static bool parseVector2(const char* str, XVECTOR2* out);

		static bool parseVector3(const char* str, XVECTOR3* out);

		static bool parseVector4(const char* str, XVECTOR4* out);

		static bool parseAxisAngle(const char* str, XQUATERNION* out);

		static bool parseColor(const char* str, XVECTOR3* out);

		static bool parseColor(const char* str, XVECTOR4* out);

	private:
		struct XAudioProperty
		{
			std::string name;
			std::string value;
			XAudioProperty(const char* name, const char* value) : name(name), value(value) { }
		};

		XAudioProperties();

		XAudioProperties(XAudioStream* stream);
		XAudioProperties(XFileBase* pFile);

		XAudioProperties(const XAudioProperties& copy);

		XAudioProperties(XAudioStream* stream, const char* name, const char* id, const char* parentID, XAudioProperties* parent);
		XAudioProperties(XFileBase* pFile, const char* name, const char* id, const char* parentID, XAudioProperties* parent);

		void readProperties(XAudioStream* stream);
		void readProperties(XFileBase* pFile);

		void setDirectoryPath(const std::string* path);

		void setDirectoryPath(const std::string& path);

		void skipWhiteSpace(XAudioStream* stream);
		void skipWhiteSpace(XFileBase* pFile);

		char* trimWhiteSpace(char* str);

		XAudioProperties* clone();

		void mergeWith(XAudioProperties* overrides);
		
		void resolveInheritance(const char* id = NULL);

		std::string                                     m_namespace;
		std::string                                     m_id;
		std::string                                     m_parentID;
		std::list<XAudioProperty>                       m_properties;
		std::list<XAudioProperty>::iterator             m_propertiesItr;
		std::vector<XAudioProperties*>                  m_namespaces;
		std::vector<XAudioProperties*>::const_iterator  m_namespacesItr;
		std::vector<XAudioProperty>*                    m_variables;
		std::string*                                    m_dirPath;
		bool                                            m_visited;
		XAudioProperties*                               m_parent;
	};
}

#endif
