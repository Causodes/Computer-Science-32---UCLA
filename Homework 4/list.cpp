void listAll(const Class* c, string path)  // two-parameter overload
{
	vector<Class*> list = c->subclasses();

	if (list.empty())						//At end of branch or no subclasses
		cout << path << c->name() << endl;		//Just print name
	else
	{
		cout << path << c->name() << endl;		//add name and => to path string
		path += c->name() + "=>";				//Print path and current name
		vector<Class*>::const_iterator it = list.begin();
		for (it; it != list.end(); it++)
			listAll(*it, path);
	}
}