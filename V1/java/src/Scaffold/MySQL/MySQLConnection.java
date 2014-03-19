package Scaffold.MySQL;

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

public class MySQLConnection implements DBConnection
{
	private Connection conn;
	private List<Routine> routines;
	private List<Table> tables;
	
	public void openConnection(String host, String port, String username, String password, String dbName)
	{
		try
		{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			conn = DriverManager.getConnection("jdbc:mysql://" + host + ":" + port + "/" + dbName, username, password);
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.exit(1);
		}
		
		loadRoutines(dbName);
		loadTables(dbName);
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
	
	public void loadRoutines(String dbName)
	{
		routines = new Vector<Routine>();
	}
	
	public void loadTables(String dbName)
	{
		tables = new Vector<Table>();
		
		try
		{
			PreparedStatement tableStatement = conn.prepareStatement("select table_name from information_schema.tables where table_schema = ?");
			PreparedStatement columnStatement = conn.prepareStatement("select column_name, data_type from information_schema.columns where table_name = ? and table_schema = ? order by ordinal_position");
			PreparedStatement keyStatement = conn.prepareStatement("select tc.constraint_type as constraint_type from information_schema.key_column_usage as kcu join information_schema.table_constraints as tc on tc.constraint_name = kcu.constraint_name where kcu.column_name = ? and kcu.table_name = ? and kcu.table_schema = ?");
			PreparedStatement foreignStatement = conn.prepareStatement("select kcu.referenced_table_name as table_name, kcu.referenced_column_name as column_name from information_schema.key_column_usage as kcu join information_schema.table_constraints as tc on tc.constraint_name = kcu.constraint_name where kcu.column_name = ? and kcu.table_name = ? and kcu.table_schema = ? and tc.constraint_type = 'foreign key'");
			
			tableStatement.setString(1, dbName);
			ResultSet tableRS = tableStatement.executeQuery();
			while (tableRS.next())
			{
				Table table = new Table();
				
				table.setName(tableRS.getString("table_name"));
				
				columnStatement.setString(1, table.getName());
				columnStatement.setString(2, dbName);
				ResultSet columnRS = columnStatement.executeQuery();
				while (columnRS.next())
				{
					Column column = new Column();
					
					column.setName(columnRS.getString("column_name"));
					column.setType(getTypeInfo(columnRS.getString("data_type")));
					
					foreignStatement.setString(1, column.getName());
					foreignStatement.setString(2, table.getName());
					foreignStatement.setString(3, dbName);
					ResultSet foreignRS = foreignStatement.executeQuery();
					ForeignKeyReference reference = null;
					while (foreignRS.next())
					{
						reference = new ForeignKeyReference();
						
						reference.setTable(foreignRS.getString("table_name"));
						reference.setColumn(foreignRS.getString("column_name"));
					}
					column.setReference(reference);
					
					keyStatement.setString(1, column.getName());
					keyStatement.setString(2, table.getName());
					keyStatement.setString(3, dbName);
					ResultSet keyRS = keyStatement.executeQuery();
					column.setIsPrimaryKey(false);
					while (keyRS.next())
					{
						if ("primary key".equalsIgnoreCase(keyRS.getString("constraint_type")))
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
		
		if (type.equalsIgnoreCase("boolean"))
		{
			typeInfo.setJavaType("Boolean");
			typeInfo.setJavaSQLType("java.sql.Types.BIT");
			typeInfo.setDbType("boolean");
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
		else if (type.equalsIgnoreCase("integer"))
		{
			typeInfo.setJavaType("Integer");
			typeInfo.setJavaSQLType("java.sql.Types.INTEGER");
			typeInfo.setDbType("integer");
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
		else if (type.equalsIgnoreCase("tinyint"))
		{
			typeInfo.setJavaType("Integer");
			typeInfo.setJavaSQLType("java.sql.Types.TINYINT");
			typeInfo.setDbType("tinyint");
		}
		
		return typeInfo;
	}
}
