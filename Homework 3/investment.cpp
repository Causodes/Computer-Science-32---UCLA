class Investment
{
public:
	Investment(string name, int price);
	virtual ~Investment();
	virtual string name() const;
	virtual int purchasePrice() const;
	virtual string description() const = 0;
	virtual bool fungible() const;
private:
	string m_name;
	int m_price;
};

class Painting : public Investment
{
public:
	Painting(string name, int price)
		:Investment(name, price) {}
	virtual ~Painting();
	virtual string description() const;
};

class Stock : public Investment
{
public:
	Stock(string name, int price, string description)
		:Investment(name, price)
	{
		m_description = description;
	}
	virtual ~Stock();
	virtual string description() const;
	virtual bool fungible() const;
private:
	string m_description;
};

class House : public Investment
{
public:
	House(string name, int price)
		:Investment(name, price) {}
	virtual ~House();
	virtual string description() const;
};

Investment::Investment(string name, int price)
{
	m_name = name;
	m_price = price;
}

Investment::~Investment() {}

string Investment::name() const
{
	return m_name;
}

int Investment::purchasePrice() const
{
	return m_price;
}

bool Investment::fungible() const
{
	return false;
}

string Investment::description() const
{
	return "";
}

Painting::~Painting()
{
	cout << "Destroying " << name() << ", a painting" << endl;
}

string Painting::description() const
{
	return "painting";
}

Stock::~Stock()
{
	cout << "Destroying " << name() << ", a stock holding" << endl;
}

string Stock::description() const
{
	return "stock trading as " + m_description;
}

bool Stock::fungible() const
{
	return true;
}

House::~House()
{
	cout << "Destroying the house " << name() << endl;
}

string House::description() const
{
	return "house";
}