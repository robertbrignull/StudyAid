package Scaffold.SQLServer;

import java.util.List;

import Scaffold.Scaffold;
import Scaffold.TypeInfo;
import Scaffold.Routine.Parameter;
import Scaffold.Routine.Routine;

public class ScalarFunction extends Routine
{
	TypeInfo returnType;
	
	public ScalarFunction(TypeInfo returnType)
	{
		super();
		
		this.returnType = returnType;
	}
	
	public String getSource()
	{
		String source = "";
		
		List<Parameter> inParameters = getParameters(Parameter.Mode.IN);
		List<Parameter> outParameters = getParameters(Parameter.Mode.OUT);
		int numInParameters = inParameters.size();
		
		
		
		if (outParameters.size() != 1)
		{
			System.out.println(getName() + " has " + outParameters.size() + " out parameters, it should have precisely one.");
			return "";
		}
		
		
		
		source += "public static " + returnType.getJavaType() + " " + getName() + "(Connection conn";
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			source += ", " + parameter.getType().getJavaType() + " " + parameter.getName();
		}
		source += ") throws java.sql.SQLException\n";
		source += "{\n";
		
		
		
		source += "\tCallableStatement stmt = conn.prepareCall(\"{? = call " + getName() + "(";
		for (int i = 0; i < numInParameters; ++i)
		{
			source += "?";
			
			if (i + 1 < numInParameters)
			{
				source += ", ";
			}
		}
		source += ")}\");\n";
		
		
		
		source += "\tstmt.registerOutParameter(1, " + returnType.getJavaSQLType() + ");\n\t\n";
		
		for (int i = 0; i < numInParameters; ++i)
		{
			Parameter parameter = inParameters.get(i);
			
			source += "\tif (" + parameter.getName() + " == null) {\n";
			source += "\t\tstmt.setNull(" + (i + 2) + ", " + parameter.getType().getJavaSQLType() + ");\n";
			source += "\t} else {\n";
			source += "\t\tstmt.set" + Scaffold.nameHack(parameter.getType().getJavaType()) + "(" + (i + 2) + ", " + parameter.getName() + ");\n";
			source += "\t}\n\t\n";
		}
		
		
		
		source += "\tstmt.executeUpdate();\n";
		source += "\t" + returnType.getJavaType() + " ret = stmt.get" + Scaffold.nameHack(returnType.getJavaType()) + "(1);\n";
		
		source += "\t\n";
		source += "\treturn ret;\n";
		source += "}\n\n\n\n";
		
		return source;
	}
}
