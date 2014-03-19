package Scaffold.Table;

import Scaffold.TypeInfo;

public class Column
{
	private String name;
	private TypeInfo type;
	private ForeignKeyReference reference;
	private boolean isPrimaryKey;
	
	
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public TypeInfo getType()
	{
		return type;
	}
	
	public void setType(TypeInfo type)
	{
		this.type = type;
	}
	
	public ForeignKeyReference getReference()
	{
		return reference;
	}
	
	public void setReference(ForeignKeyReference reference)
	{
		this.reference = reference;
	}
	
	public boolean getIsPrimaryKey()
	{
		return isPrimaryKey;
	}
	
	public void setIsPrimaryKey(boolean isPrimaryKey)
	{
		this.isPrimaryKey = isPrimaryKey;
	}
}
