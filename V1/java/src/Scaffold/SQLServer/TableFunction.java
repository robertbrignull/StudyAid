package Scaffold.SQLServer;

import java.util.List;

import Scaffold.Scaffold;
import Scaffold.Routine.Parameter;
import Scaffold.Routine.Routine;

public class TableFunction extends Routine
{
	public TableFunction()
	{
		super();
	}
	
	public String getSource()
	{
		String source = "";
		
		List<Parameter> inParameters = getParameters(Parameter.Mode.IN);
		int numInParameters = inParameters.size();
		
		
		
		source += "public static ResultSet " + getName() + "(Connection conn";
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			source += ", " + parameter.getType().getJavaType() + " " + parameter.getName();
		}
		source += ") throws java.sql.SQLException\n";
		source += "{\n";
		
		
		
		source += "\tPreparedStatement stmt = conn.prepareStatement(\"select * from " + getName() + "(";
		for (int i = 0; i < numInParameters; ++i)
		{
			source += "?";
			
			if (i + 1 < numInParameters)
			{
				source += ", ";
			}
		}
		source += ")\", ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);\n";
		
		
		
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			
			source += "\tif (" + parameter.getName() + " == null) {\n";
			source += "\t\tstmt.setNull(" + (i + 1) + ", " + parameter.getType().getJavaSQLType() + ");\n";
			source += "\t} else {\n";
			source += "\t\tstmt.set" + Scaffold.nameHack(parameter.getType().getJavaType()) + "(" + (i + 1) + ", " + parameter.getName() + ");\n";
			source += "\t}\n\t\n";
		}
		
		
		
		source += "\tResultSet rs = stmt.executeQuery();\n";
		
		source += "\t\n";
		source += "\treturn rs;\n";
		source += "}\n\n\n\n";
		
		return source;
	}
}
