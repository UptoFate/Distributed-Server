#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_
#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>
#include<sstream>
#include<vector>
#include<set>
using namespace std;

/**
 * properties配置文件操作工具类
 */
class Properties final
{
private:
	map<string, string>* props = nullptr;
	set<string>* keys = nullptr;
	void trim(string& s);
	vector<string> split(const string& str, char pattern);
	void loadKeys();
public:
	Properties();
	~Properties();
	map<string, string>* getProps() const;
	set<string>* getKeys() const;
	//加载指定位置配置
	bool load(const string& path);
	//通过key获取属性值
	string getProperty(const string& key);
	//设置属性值
	void setProperty(const string& key, const string& value);
	//移除属性
	void remProperty(const string& key);
	//保存配置到指定位置
	bool save(const string& path);
};

/**
 * 创建Properties对象
 * @param varName Properties对象实例对应的变量名
 * @param fileName config目录下面的配置文件名称
 */
#define CREATE_PROPERTIES(varName, fileName) \
Properties varName; \
varName.load("config/"#fileName".properties")

#endif // _PROPERTIES_H_