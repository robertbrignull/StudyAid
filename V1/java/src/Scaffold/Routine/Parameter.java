package Scaffold.Routine;

import Scaffold.TypeInfo;

public class Parameter
{
	public enum Mode
	{
		IN, OUT, INOUT;
	}
	
	
	
	private Mode mode;
	private String name;
	private TypeInfo type;
	
	
	
	public Mode getMode()
	{
		return mode;
	}
	
	public void setMode(Mode mode)
	{
		this.mode = mode;
	}
	
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
}
