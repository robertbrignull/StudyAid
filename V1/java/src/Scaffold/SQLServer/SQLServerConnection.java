package Scaffold.SQLServer;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import Scaffold.DBConnection;
import Scaffold.TypeInfo;
import Scaffold.Routine.Parameter;
import Scaffold.Routine.Routine;
import Scaffold.Table.Column;
import Scaffold.Table.ForeignKeyReference;
import Scaffold.Table.Table;

public class SQLServerConnection implements DBConnection
{
	private Connection conn;
	private List<Routine> routines;
	private List<Table> tables;
	
	public void openConnection(String host, String port, String username, String password, String dbName)
	{
		try
		{
			Class.forName("com.microsoft.SQLServer.jdbc.SQLServerDriver");
			conn = DriverManager.getConnection("jdbc:SQLServer://" + host + ":" + port + ";databaseName=" + dbName, username, password);
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.exit(1);
		}
		
		loadRoutines();
		loadTables();
	}

	public void closeConnection()
	{
		if (conn != null)
		{
			try
			{
				conn.close();
			}
			catch (SQLException e)
			{
				e.printStackTrace();
			}
		}
	}

	public Collection<Routine> getRoutines()
	{
		return routines;
	}

	public Collection<Table> getTables()
	{
		return tables;
	}
	
	public void loadRoutines()
	{
		routines = new Vector<Routine>();
		
		try
		{
			PreparedStatement routineStatement = conn.prepareStatement("select specific_name, routine_type, data_type from information_schema.routines where routine_type in ('procedure', 'function') order by specific_name asc");
			PreparedStatement parameterStatement = conn.prepareStatement("select parameter_name, data_type, parameter_mode from information_schema.parameters where specific_name = ? order by ordinal_position asc");
			
			ResultSet routineRS = routineStatement.executeQuery();
			while (routineRS.next())
			{
				Routine routine = null;
				
				if ("function".equalsIgnoreCase(routineRS.getString("routine_type")))
				{
					String data_type = routineRS.getString("data_type");
					
					if ("table".equalsIgnoreCase(data_type))
					{
						routine = new TableFunction();
					}
					else
					{
						routine = new ScalarFunction(getTypeInfo(data_type));
					}
				}
				else
				{
					routine = new StoredProcedure();
				}
				
				routine.setName(routineRS.getString("specific_name"));
				
				parameterStatement.setString(1, routine.getName());
				ResultSet parameterRS = parameterStatement.executeQuery();
				while (parameterRS.next())
				{
					Parameter parameter = new Parameter();
					
					parameter.setName(parameterRS.getString("parameter_name").replaceAll("@", ""));
					parameter.setMode(Parameter.Mode.valueOf(parameterRS.getString("parameter_mode")));
					parameter.setType(getTypeInfo(parameterRS.getString("data_type")));
					
					routine.addParameter(parameter);
				}
				
				routines.add(routine);
			}
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	public void loadTables()
	{
		tables = new Vector<Table>();
		
		try
		{
			PreparedStatement tableStatement = conn.prepareStatement("select name from sys.objects where type = 'U' order by name asc");
			PreparedStatement columnStatement = conn.prepareStatement("select column_name, data_type from information_schema.columns where table_name = ? order by ordinal_position");
			PreparedStatement foreignStatement = conn.prepareStatement("select target.table_name as target_table, target.column_name as target_column from information_schema.referential_constraints as rc join information_schema.key_column_usage as source on source.constraint_name = rc.constraint_name join information_schema.key_column_usage as target on target.constraint_name = rc.unique_constraint_name where source.table_name = ? and source.column_name = ?");
			PreparedStatement primaryKeyStatement = conn.prepareStatement("select constraint_type from information_schema.table_constraints as tc join information_schema.constraint_column_usage as cu on cu.constraint_name = tc.constraint_name where tc.table_name = ? and cu.column_name = ?");
			
			ResultSet tableRS = tableStatement.executeQuery();
			while (tableRS.next())
			{
				Table table = new Table();
				
				table.setName(tableRS.getString("name"));
				
				columnStatement.setString(1, table.getName());
				ResultSet columnRS = columnStatement.executeQuery();
				while (columnRS.next())
				{
					Column column = new Column();
					
					column.setName(columnRS.getString("column_name"));
					column.setType(getTypeInfo(columnRS.getString("data_type")));
					
					foreignStatement.setString(1, table.getName());
					foreignStatement.setString(2, column.getName());
					ResultSet foreignRS = foreignStatement.executeQuery();
					ForeignKeyReference reference = null;
					while (foreignRS.next())
					{
						reference = new ForeignKeyReference();
						
						reference.setTable(foreignRS.getString("target_table"));
						reference.setColumn(foreignRS.getString("target_column"));
					}
					column.setReference(reference);
					
					primaryKeyStatement.setString(1, table.getName());
					primaryKeyStatement.setString(2, column.getName());
					ResultSet uniqueRS = primaryKeyStatement.executeQuery();
					column.setIsPrimaryKey(false);
					while (uniqueRS.next())
					{
						if ("primary key".equalsIgnoreCase(uniqueRS.getString("constraint_type")))
						{
							column.setIsPrimaryKey(true);
						}
					}
					
					table.addColumn(column);
				}
				
				tables.add(table);
			}
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	public TypeInfo getTypeInfo(String type)
	{
		TypeInfo typeInfo = new TypeInfo();
		
		if (type.equalsIgnoreCase("bit"))
		{
			typeInfo.setJavaType("Boolean");
			typeInfo.setJavaSQLType("java.sql.Types.BIT");
			typeInfo.setDbType("bit");
		}
		else if (type.equalsIgnoreCase("date"))
		{
			typeInfo.setJavaType("Timestamp");
			typeInfo.setJavaSQLType("java.sql.Types.DATE");
			typeInfo.setDbType("date");
		}
		else if (type.equalsIgnoreCase("datetime"))
		{
			typeInfo.setJavaType("Timestamp");
			typeInfo.setJavaSQLType("java.sql.Types.TIMESTAMP");
			typeInfo.setDbType("datetime");
		}
		else if (type.equalsIgnoreCase("float"))
		{
			typeInfo.setJavaType("Float");
			typeInfo.setJavaSQLType("java.sql.Types.FLOAT");
			typeInfo.setDbType("float");
		}
		else if (type.equalsIgnoreCase("int"))
		{
			typeInfo.setJavaType("Integer");
			typeInfo.setJavaSQLType("java.sql.Types.INTEGER");
			typeInfo.setDbType("int");
		}
		else if (type.equalsIgnoreCase("nvarchar"))
		{
			typeInfo.setJavaType("String");
			typeInfo.setJavaSQLType("java.sql.Types.NVARCHAR");
			typeInfo.setDbType("nvarchar");
		}
		else if (type.equalsIgnoreCase("smallint"))
		{
			typeInfo.setJavaType("Integer");
			typeInfo.setJavaSQLType("java.sql.Types.SMALLINT");
			typeInfo.setDbType("smallint");
		}
		else if (type.equalsIgnoreCase("text"))
		{
			typeInfo.setJavaType("String");
			typeInfo.setJavaSQLType("java.sql.Types.VARCHAR");
			typeInfo.setDbType("text");
		}
		else if (type.equalsIgnoreCase("time"))
		{
			typeInfo.setJavaType("Timestamp");
			typeInfo.setJavaSQLType("java.sql.Types.TIME");
			typeInfo.setDbType("time");
		}
		else if (type.equalsIgnoreCase("varchar"))
		{
			typeInfo.setJavaType("String");
			typeInfo.setJavaSQLType("java.sql.Types.VARCHAR");
			typeInfo.setDbType("varchar");
		}
		
		return typeInfo;
	}
}
