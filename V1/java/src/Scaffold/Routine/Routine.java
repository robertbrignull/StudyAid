package Scaffold.Routine;

import java.util.List;
import java.util.Vector;

public abstract class Routine
{
	private String name;
	private List<Parameter> parameters;
	
	
	
	public Routine()
	{
		parameters = new Vector<Parameter>();
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public List<Parameter> getParameters()
	{
		return parameters;
	}
	
	public List<Parameter> getParameters(Parameter.Mode mode)
	{
		List<Parameter> filteredParameters = new Vector<Parameter>();
		
		for (Parameter parameter : parameters)
		{
			if (parameter.getMode() == mode)
			{
				filteredParameters.add(parameter);
			}
		}
		
		return filteredParameters;
	}
	
	public void setParameters(List<Parameter> parameters)
	{
		this.parameters = parameters;
	}
	
	public void addParameter(Parameter parameter)
	{
		parameters.add(parameter);
	}
	
	public abstract String getSource();
	
	public String getLoggingCode()
	{
		List<Parameter> inParameters = getParameters(Parameter.Mode.IN);
		int numInParameters = inParameters.size();
		String source = "";
		
		// seeing as this section already relied on there being stored procedures AuditLog_NewEntry and AuditLog_AddArgument,
		// I don't think it's too bad to make it even more specific in the name of performance
		source += "\t\t\n";
		source += "\t\tMap<String, Object> results = AuditLog_NewEntry(conn, audit_log_user, \"" + getName() +"\");\n";
		
		source += "\t\tif (results == null) return null;\n";
		
		source += "\t\tint entryId = (Integer) results.get(\"entryId\");\n";
		
		source += "\t\t\n";
		source += "\t\tstmt = conn.prepareCall(\"exec AuditLog_AddArgument ?, ?, ?, null\");\n";
		source += "\t\t\n";
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			
			/*
			source += "\t\tAuditLog_AddArgument(conn, entryId, \"" + parameter.getName() + "\",";
			source += "(" + parameter.getName() + " == null) ? \"null\" : " + parameter.getName() + ".toString());\n";
			*/
			
			source += "\t\tstmt.setInt(1, entryId);\n";
			source += "\t\tstmt.setString(2, \"" + parameter.getName() + "\");\n";
			source += "\t\tstmt.setString(3, (" + parameter.getName() + " == null) ? \"null\" : " + parameter.getName() + ".toString());\n";
			source += "\t\tstmt.execute();\n";
			source += "\t\t\n";
		}
		
		return source;
	}
}
