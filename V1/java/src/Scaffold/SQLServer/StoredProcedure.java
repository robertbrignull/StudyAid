package Scaffold.SQLServer;

import java.util.List;

import Scaffold.Scaffold;
import Scaffold.Routine.Parameter;
import Scaffold.Routine.Routine;

public class StoredProcedure extends Routine
{
	public StoredProcedure()
	{
		super();
	}
	
	public String getSource()
	{
		String source = "";
		
		List<Parameter> allParameters = getParameters();
		List<Parameter> inParameters = getParameters(Parameter.Mode.IN);
		int numParameters = allParameters.size();
		int numInParameters = inParameters.size();
		
		
		
		source += "public static Map<String, Object> " + getName() + "(Connection conn";
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			source += ", " + parameter.getType().getJavaType() + " " + parameter.getName();
		}
		source += ") throws java.sql.SQLException\n";
		source += "{\n";
		
		
		
		source += "\tCallableStatement stmt = conn.prepareCall(\"{? = call " + getName() + "(";
		for (int i = 0; i < numParameters; ++i)
		{
			source += "?";
			
			if (i + 1 < numParameters)
			{
				source += ", ";
			}
		}
		source += ")}\");\n";
		
		
		
		source += "\tstmt.registerOutParameter(1, java.sql.Types.INTEGER);\n\t\n";
		
		for (int i = 0; i < numParameters; ++i)
		{
			Parameter parameter = allParameters.get(i);
			
			if (parameter.getMode() == Parameter.Mode.IN)
			{
				source += "\tif (" + parameter.getName() + " == null) {\n";
				source += "\t\tstmt.setNull(" + (i + 2) + ", " + parameter.getType().getJavaSQLType() + ");\n";
				source += "\t} else {\n";
				source += "\t\tstmt.set" + Scaffold.nameHack(parameter.getType().getJavaType()) + "(" + (i + 2) + ", " + parameter.getName() + ");\n";
				source += "\t}\n\t\n";
			}
			else if (parameter.getMode() == Parameter.Mode.OUT || parameter.getMode() == Parameter.Mode.INOUT)
			{
				source += "\tstmt.registerOutParameter(" + (i + 2) + ", " + parameter.getType().getJavaSQLType() + ");\n\t\n";
			}
		}
		
		
		
		source += "\tstmt.executeUpdate();\n\t\n";
		source += "\tif (stmt.getInt(1) != 0) {\n";
		source += "\t\treturn null;\n";
		source += "\t} else {\n";
		source += "\t\tMap<String, Object> hm = new HashMap<String, Object>(" + numParameters + ");\n";
		
		for (int i = 0; i < numParameters; ++i)
		{
			Parameter parameter = allParameters.get(i);
			
			if (parameter.getMode() == Parameter.Mode.OUT || parameter.getMode() == Parameter.Mode.INOUT)
			{
				source += "\t\thm.put(\"" + parameter.getName() + "\", stmt.get" + Scaffold.nameHack(parameter.getType().getJavaType()) + "(" + (i + 2) + "));\n";
			}
		}
		
		source += "\t\t\n";
		source += "\t\treturn hm;\n";
		source += "\t}\n";
		source += "}\n\n\n\n";
		
		return source;
	}
}
