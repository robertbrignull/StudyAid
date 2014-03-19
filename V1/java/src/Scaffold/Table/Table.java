package Scaffold.Table;

import java.util.Collection;
import java.util.List;
import java.util.Vector;

import Scaffold.Scaffold;

public class Table
{
	private String name;
	private List<Column> columns;
	
	
	
	
	public Table()
	{
		columns = new Vector<Column>();
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public List<Column> getColumns()
	{
		return columns;
	}
	
	public void setColumns(List<Column> columns)
	{
		this.columns = columns;
	}
	
	public void addColumn(Column column)
	{
		columns.add(column);
	}
	
	public String getSource(Collection<Table> tables)
	{
		String source = "";
		
		source += conditionClass() + "\t\n\t\n\t\n";
		source += constructor() + "\t\n\t\n\t\n";
		source += connVariableAndGetter() + "\t\n\t\n\t\n";
		source += memberVariables(tables) + "\t\n\t\n\t\n";
		source += memberGettersSetters(tables) + "\t\n\t\n\t\n";
		source += otherTableGets(tables) + "\t\n\t\n\t\n";
		source += loadFromTable() + "\t\n\t\n\t\n";
		source += get() + "\t\n\t\n\t\n";
		source += count() + "\t\n\t\n\t\n";
		source += create() + "\t\n\t\n\t\n";
		source += update() + "\t\n\t\n\t\n";
		source += delete() + "\t\n\t\n\t\n";
		source += reload() + "\t\n\t\n\t\n";
		source += stringHack() + "\t\n\t\n\t\n";
		
		return source;
	}
	
	private String conditionClass()
	{
		String source = "";
		
		// This class is used to pass to the get method and should allow full control
		// over the conditioning.
		// In theory, any condition that can be made from the statements and, or, ==, !=
		// can be represented using this class. The added benefit is that it'll be done
		// in a compiler friendly way so you know everything is syntactically correct.
		source += "\tpublic static class Condition {\n";
		
		source += "\t\tprivate static enum SetState {\n";
		source += "\t\t\tUnset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;\n";
		source += "\t\t}\n";
		source += "\t\t\n";
		
		for (Column column : columns)
		{
			source += "\t\tprivate " + column.getType().getJavaType() + " m_" + column.getName() + ";\n";
			source += "\t\tprivate SetState m_" + column.getName() + "_set;\n";
		}
		
		source += "\t\t\n";
		source += "\t\tList<Condition> alternatives;\n";
		source += "\t\tList<Condition> requirements;\n";
		
		source += "\t\t\n\t\t\n\t\t\n";
		
		source += "\t\tpublic Condition() {\n";
		for (Column column : columns)
		{
			source += "\t\t\tm_" + column.getName() + "_set = SetState.Unset;\n";
		}
		source += "\t\t\talternatives = new Vector<Condition>();\n";
		source += "\t\t\trequirements = new Vector<Condition>();\n";
		source += "\t\t}\n";
		
		source += "\t\t\n\t\t\n\t\t\n";
		
		for (Column column : columns)
		{
			source += "\t\tpublic Condition " + column.getName() + "(" + column.getType().getJavaType();
			source += " p_" + column.getName() + ") {\n";
			source += "\t\t\tm_" + column.getName() + " = p_" + column.getName() + ";\n";
			source += "\t\t\tm_" + column.getName() + "_set = (p_" + column.getName();
			source += " == null) ? SetState.Null : SetState.Equal;\n";
			source += "\t\t\treturn this;\n";
			source += "\t\t}\n";
			source += "\t\t\n";
			
			source += "\t\tpublic Condition " + column.getName() + "Not(" + column.getType().getJavaType();
			source += " p_" + column.getName() + ") {\n";
			source += "\t\t\tm_" + column.getName() + " = p_" + column.getName() + ";\n";
			source += "\t\t\tm_" + column.getName() + "_set = (p_" + column.getName();
			source += " == null) ? SetState.NotNull : SetState.NotEqual;\n";
			source += "\t\t\treturn this;\n";
			source += "\t\t}\n";
			source += "\t\t\n";
			
			source += "\t\tpublic Condition " + column.getName() + "LessThan(" + column.getType().getJavaType();
			source += " p_" + column.getName() + ") {\n";
			source += "\t\t\tm_" + column.getName() + " = p_" + column.getName() + ";\n";
			source += "\t\t\tm_" + column.getName() + "_set = (p_" + column.getName();
			source += " == null) ? SetState.Unset : SetState.LessThan;\n";
			source += "\t\t\treturn this;\n";
			source += "\t\t}\n";
			source += "\t\t\n";
			
			source += "\t\tpublic Condition " + column.getName() + "MoreThan(" + column.getType().getJavaType();
			source += " p_" + column.getName() + ") {\n";
			source += "\t\t\tm_" + column.getName() + " = p_" + column.getName() + ";\n";
			source += "\t\t\tm_" + column.getName() + "_set = (p_" + column.getName();
			source += " == null) ? SetState.Unset : SetState.MoreThan;\n";
			source += "\t\t\treturn this;\n";
			source += "\t\t}\n";
			source += "\t\t\n";
		}
		
		source += "\t\t\n\t\t\n\t\t\n";
		
		source += "\t\tpublic Condition or(Condition condition) {\n";
		source += "\t\t\talternatives.add(condition);\n";
		source += "\t\t\treturn this;\n";
		source += "\t\t}\n";
		
		source += "\t\tpublic Condition and(Condition condition) {\n";
		source += "\t\t\trequirements.add(condition);\n";
		source += "\t\t\treturn this;\n";
		source += "\t\t}\n";
		
		source += "\t\t\n\t\t\n\t\t\n";
		
		source += "\t\tpublic String getWhereClause() {\n";
		source += "\t\t\tString sql = \"(((1 = 1)\";\n";
		for (Column column : columns)
		{
			source += "\t\t\tif (m_" + column.getName() + "_set == SetState.Equal) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " = \" + " + formatForSQL(column) + ";\n";
			source += "\t\t\t} else if (m_" + column.getName() + "_set == SetState.NotEqual) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " <> \" + " + formatForSQL(column) + ";\n";
			source += "\t\t\t} else if (m_" + column.getName() + "_set == SetState.Null) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " is null\";\n";
			source += "\t\t\t} else if (m_" + column.getName() + "_set == SetState.NotNull) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " is not null\";\n";
			source += "\t\t\t} else if (m_" + column.getName() + "_set == SetState.LessThan) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " < \" + " + formatForSQL(column) + ";\n";
			source += "\t\t\t} else if (m_" + column.getName() + "_set == SetState.MoreThan) {\n";
			source += "\t\t\t\tsql += \" and " + column.getName() + " > \" + " + formatForSQL(column) + ";\n";
			source += "\t\t\t}\n";
			source += "\t\t\t\n";
		}
		source += "\t\t\tsql += \")\";\n";
		source += "\t\t\t\n";
		source += "\t\t\tfor (Condition condition : requirements) {\n";
		source += "\t\t\t\tsql += \" and \" + condition.getWhereClause();\n";
		source += "\t\t\t}\n";
		source += "\t\t\t\n";
		source += "\t\t\tif (alternatives.size() > 0) {\n";
		source += "\t\t\t\tsql += \" and (\";\n";
		source += "\t\t\t\tboolean first = true;\n";
		source += "\t\t\t\tfor (Condition condition : alternatives) {\n";
		source += "\t\t\t\t\tif (!first) {\n";
		source += "\t\t\t\t\t\tsql += \" or \";\n";
		source += "\t\t\t\t\t}\n";
		source += "\t\t\t\t\tfirst = false;\n";
		source += "\t\t\t\t\tsql += condition.getWhereClause();\n";
		source += "\t\t\t\t}\n";
		source += "\t\t\t\tsql += \")\";\n";
		source += "\t\t\t}\n";
		source += "\t\t\tsql += \")\";\n";
		source += "\t\t\treturn sql;\n";
		source += "\t\t}\n";
		
		source += "\t}\n";
		
		return source;
	}
	
	private String formatForSQL(Column column)
	{
		String type = column.getType().getJavaType();
		
		if (type.equalsIgnoreCase("Boolean"))
		{
			return "(m_" + column.getName() + " == null ? \"null\" : m_" + column.getName() + " ? \"'1'\" : \"'0'\")";
		}
		else if (type.equalsIgnoreCase("Timestamp"))
		{
			return "(m_" + column.getName() + " == null ? \"null\" : (\"'\" + m_" + column.getName() + ".toString().substring(0, 19) + \"'\"))";
		}
		else if (type.equalsIgnoreCase("Float"))
		{
			return "(m_" + column.getName() + " == null ? \"null\" : m_" + column.getName() + ".toString())";
		}
		else if (type.equalsIgnoreCase("Integer"))
		{
			return "(m_" + column.getName() + " == null ? \"null\" : m_" + column.getName() + ".toString())";
		}
		else if (type.equalsIgnoreCase("String"))
		{
			return "(m_" + column.getName() + " == null ? \"null\" : (\"'\" + stringHack(m_" + column.getName() + ") + \"'\"))";
		}
		
		return "";
	}
	
	private String constructor()
	{
		String source = "";
		
		source += "\tpublic " + name + "(Connection p_conn) {\n";
		source += "\t\tm_conn = p_conn;\n";
		source += "\t}\n";
		
		return source;
	}
	
	private String connVariableAndGetter()
	{
		String source = "";
		
		source += "\tprivate Connection m_conn;\n";
		source += "\t\n";
		source += "\tpublic Connection getConn() {\n";
		source += "\t\treturn m_conn;\n";
		source += "\t}\n";
		
		return source;
	}
	
	private String memberVariables(Collection<Table> tables)
	{
		String source = "";
		
		// Define member variables, all of them should be private, all access should be by getters and setters,
		// this allows us to fully encapsulate how we interact with the database, so referenced rows can only
		// be loaded when requested and updated rows again only loaded when needed.
		for (Column column : columns)
		{
			ForeignKeyReference reference = column.getReference();
			
			// all variables will have the same names as ones in the database
			source += "\tprivate " + column.getType().getJavaType() + " m_" + column.getName() + ";\n";
			
			// if it's a foreign key reference we'll need to store the actual
			// referenced row as well as the value that identifies it
			if (reference != null)
			{
				String tableName = getTableName(tables, reference.getTable());
				source += "\tprivate " + tableName + " m_" + column.getName() + "_record;\n";
			}
		}
		
		return source;
	}
	
	private String memberGettersSetters(Collection<Table> tables)
	{
		String source = "";
		
		// Define getters and setters for all member variables.
		// When getting, the user should not know if they're dealing with a primitive type or
		// a table reference, the experience should be the same.
		// When setting, for convenience we'll allow the user to either set using the referenced column
		// or by passing a whole table object.
		// This enables either a high level of abstraction and direct control depending on the situation.
		for (Column column : columns)
		{
			ForeignKeyReference reference = column.getReference();
			
			if (reference == null)
			{
				// very simple getter and setter methods as we're only dealing with primitive types rather than tables
				source += "\tpublic " + column.getType().getJavaType() + " get" + capFirst(column.getName()) + "() {\n";
				source += "\t\treturn m_" + column.getName() + ";\n";
				source += "\t}\n";
				source += "\t\n";
				
				source += "\tpublic void set" + capFirst(column.getName()) + "(";
				source += column.getType().getJavaType() + " p_" + column.getName() + ") {\n";
				source += "\t\tm_" + column.getName() + " = p_" + column.getName() + ";\n";
				source += "\t}\n";
				source += "\t\n";
			}
			else
			{
				String tableName = getTableName(tables, reference.getTable());
				
				// downloads record if necessary, otherwise just returns one from before
				source += "\tpublic " + tableName + " get" + capFirst(column.getName()) + "Record() throws SQLException {\n";
				source += "\t\tif (m_" + column.getName() + "_record == null) {\n";
				source += "\t\t\t" + tableName + ".Condition condition = new " + tableName + ".Condition();\n";
				source += "\t\t\tcondition." + reference.getColumn() + "(m_" + column.getName() + ");\n";
				source += "\t\t\tList<" + tableName + "> list = " + tableName + ".get(m_conn, condition);\n";
				source += "\t\t\tif (list.size() == 0) {\n";
				source += "\t\t\t\tm_" + column.getName() + "_record = null;\n";
				source += "\t\t\t} else {\n";
				source += "\t\t\t\tm_" + column.getName() + "_record = list.get(0);\n";
				source += "\t\t\t}\n";
				source += "\t\t}\n";
				source += "\t\treturn m_" + column.getName() + "_record;\n";
				source += "\t}\n";
				source += "\t\n";
				
				// doesn't download, just returns the value used as reference
				source += "\tpublic " + column.getType().getJavaType() + " get" + capFirst(column.getName()) + " () {\n";
				source += "\t\treturn m_" + column.getName() + ";\n";
				source += "\t}\n";
				source += "\t\n";
				
				// sets based on the referenced column,
				// sets record to be null so it'll be reloaded
				source += "\tpublic void set" + capFirst(column.getName()) + "(";
				source += column.getType().getJavaType() + " p_" + column.getName() + ") {\n";
				source += "\t\tm_" + column.getName() + " = p_" + column.getName();
				source += ";\n";
				source += "\t\tm_" + column.getName() + "_record = null;\n";
				source += "\t}\n";
				source += "\t\n";
				
				// sets using an entire table object,
				// sets both reference and record if possible
				source += "\tpublic void set" + capFirst(column.getName()) + "Record(";
				source += tableName + " p_" + column.getName() + ") {\n";
				source += "\t\tm_" + column.getName() + "_record = p_" + column.getName() + ";\n";
				source += "\t\tif (p_" + column.getName() + " != null) {\n";
				source += "\t\t\tm_" + column.getName() + " = p_" + column.getName();
				source += ".get" + capFirst(reference.getColumn()) + "();\n";
				source += "\t\t}\n";
				source += "\t}\n";
				source += "\t\n";
			}
		}
		
		return source;
	}
	
	private	String otherTableGets(Collection<Table> tables)
	{
		String source = "";
		
		for (Table table : tables)
		{
			for (Column column : table.getColumns())
			{
				ForeignKeyReference reference = column.getReference();
				if (reference != null && reference.getTable().equalsIgnoreCase(getName()))
				{
					source += "\tpublic List<" + table.getName() + "> get" + capFirst(table.getName()) + "sWith" + capFirst(column.getName()) + "() throws SQLException {\n";
					source += "\t\t" + table.getName() + ".Condition cond = new " + table.getName() + ".Condition();\n";
					source += "\t\tcond." + column.getName() + "(m_" + reference.getColumn() + ");\n";
					source += "\t\treturn " + table.getName() + ".get(m_conn, cond);\n";
					source += "\t}\n";
					source += "\t\n";
				}
			}
		}
		
		return source;
	}
	
	private String loadFromTable()
	{
		String source = "";
		
		source += "\tpublic void loadFrom" + capFirst(name) + "(" + name + " obj) {\n";
		source += "\t\tm_conn = obj.m_conn;\n";
		for (Column column : columns)
		{
			source += "\t\tm_" + column.getName() + " = obj.m_" + column.getName() + ";\n";
			
			if (column.getReference() != null)
			{
				source += "\t\tm_" + column.getName() + "_record = null;\n";
			}
		}
		source += "\t}\n";
		
		return source;
	}
	
	private String get()
	{
		String source = "";
		
		source += "\tpublic static List<" + name + "> get(Connection conn, Condition condition) throws SQLException {\n";
		
		source += "\t\tif (conn == null) {\n";
		source += "\t\t\treturn new Vector<" + name + ">();\n";
		source += "\t\t}\n";
		source += "\t\t\n";
		
		source += "\t\tString sql = \"select * from " + name + " where \";\n";
		source += "\t\tsql += (condition == null) ? \"1 = 1\" : condition.getWhereClause();\n";
//source += "System.out.println(\"Where clause: \" + sql);\n";
		source += "\t\t\n";
		source += "\t\tResultSet rs = conn.createStatement().executeQuery(sql);\n";
		source += "\t\tList<" + name + "> list = new Vector<" + name + ">();\n";
		source += "\t\t\n";
		source += "\t\twhile (rs.next()) {\n";
		
		source += "\t\t" + name + " obj = new " + name + "(conn);\n";
		int i = 0;
		for (Column column : columns)
		{
			source += "\t\t\t\n";
			source += "\t\t\t" + column.getType().getJavaType() + " data" + i + " = rs.get" + Scaffold.nameHack(column.getType().getJavaType());
			source += "(\"" + column.getName() + "\");\n";
			source += "\t\t\tif (rs.wasNull()) {\n";
			source += "\t\t\t\tdata" + i + " = null;\n";
			source += "\t\t\t}\n";
			source += "\t\t\tobj.set" + capFirst(column.getName()) + "(data" + i + ");\n";
			i += 1;
		}
		source += "\t\tlist.add(obj);\n";
		
		source += "\t\t}\n";
		source += "\t\t\n";
		source += "\t\treturn list;\n";
		
		source += "\t}\n";
		
		return source;
	}
	
	private String count()
	{
		String source = "";
		
		source += "\tpublic static int count(Connection conn, Condition condition) throws SQLException {\n";
		
		source += "\t\tif (conn == null) {\n";
		source += "\t\t\treturn 0;\n";
		source += "\t\t}\n";
		source += "\t\t\n";
		
		source += "\t\tString sql = \"select count(*) from " + name + " where \";\n";
		source += "\t\tsql += (condition == null) ? \"1 = 1\" : condition.getWhereClause();\n";
//source += "System.out.println(\"Where clause: \" + sql);\n";
		source += "\t\t\n";
		source += "\t\tResultSet rs = conn.createStatement().executeQuery(sql);\n";
		source += "\t\trs.next();\n";
		source += "\t\t\n";
		source += "\t\treturn rs.getInt(1);\n";
		
		source += "\t}\n";
		
		return source;
	}
	
	private String create()
	{
		String source = "";
		
		source += "\tpublic void create() throws SQLException {\n";
		source += "\t\tString sql = \"insert into " + name + " (\";\n";
		boolean firstInList = true;
		for (Column column : columns)
		{
			if (!column.getIsPrimaryKey())
			{
				source += "\t\tsql += ";
				if (!firstInList)
				{
					source += "\", \" + ";
				}
				firstInList = false;
				source += "\"" + column.getName() + "\";\n";
			}
		}
		source += "\t\tsql += \") values (\";\n";
		firstInList = true;
		for (Column column : columns)
		{
			if (!column.getIsPrimaryKey())
			{
				source += "\t\tsql += ";
				if (!firstInList)
				{
					source += "\", \" + ";
				}
				firstInList = false;
				source += formatForSQL(column) + ";\n";
			}
		}
		source += "\t\tsql += \")\";\n";
//source += "System.out.println(\"Create: \" + sql);\n";
		source += "\t\t\n";
		source += "\t\tm_conn.createStatement().executeUpdate(sql);\n";
		source += "\t\t\n";
		source += "\t\tResultSet rs = m_conn.createStatement().executeQuery(\"select last_insert_id() as key_out\");\n";
		source += "\t\trs.next();\n";
		for (Column column : columns)
		{
			if (column.getIsPrimaryKey())
			{
				source += "\t\tm_" + column.getName() + " = rs.get" + Scaffold.nameHack(column.getType().getJavaType()) + "(\"key_out\");\n";
			}
		}
		
		source += "\t}\n";
		
		return source;
	}
	
	private String update()
	{
		String source = "";
		
		source += "\tpublic void update() throws SQLException {\n";
		
		source += "\t\tString sql = \"update " + name + " set \";\n";
		boolean firstInList = true;
		for (Column column : columns)
		{
			if (!column.getIsPrimaryKey())
			{
				source += "\t\tsql += ";
				if (!firstInList)
				{
					source += "\", \" + ";
				}
				firstInList = false;
				source += "\"" + column.getName() + " = \" + " + formatForSQL(column) + ";\n";
			}
		}
		source += "\t\tsql += \" where (1 = 1)\";\n";
		for (Column column : columns)
		{
			if (column.getIsPrimaryKey())
			{
				source += "\t\tsql += \" and " + column.getName() + " = \" + " + formatForSQL(column) + ";\n";
			}
		}
//source += "System.out.println(\"Update: \" + sql);\n";
		source += "\t\t\n";
		source += "\t\tm_conn.createStatement().executeUpdate(sql);\n";
		
		source += "\t}\n";
		
		return source;
	}
	
	private String delete()
	{
		String source = "";
		
		source += "\tpublic void delete() throws SQLException {\n";
		
		source += "\t\tString sql = \"delete from " + name + " where 1 = 1\";\n";
		for (Column column : columns)
		{
			if (column.getIsPrimaryKey())
			{
				source += "\t\tsql += \" and " + column.getName() + " = \" + " + formatForSQL(column) + ";\n";
			}
		}
//source += "System.out.println(\"Delete: \" + sql);\n";
		source += "\t\t\n";
		source += "\t\tm_conn.createStatement().executeUpdate(sql);\n";
		
		source += "\t}\n";
		
		return source;
	}	
	
	private String reload()
	{
		String source = "";
		
		source += "\tpublic void reload() throws SQLException {\n";
		
		source += "\t\tString sql = \"select * from " + name + " where (1 = 1)\";\n";
		for (Column column : columns)
		{
			if (column.getIsPrimaryKey())
			{
				source += "\t\tsql += \" and " + column.getName() + " = \" + " + formatForSQL(column) + ";\n";
			}
		}
		source += "\t\t\n";
		source += "\t\tResultSet rs = m_conn.createStatement().executeQuery(sql);\n";
		source += "\t\trs.next();\n";
		int i = 0;
		for (Column column : columns)
		{
			source += "\t\t\n";
			source += "\t\t" + column.getType().getJavaType() + " data" + i + " = rs.get" + Scaffold.nameHack(column.getType().getJavaType());
			source += "(\"" + column.getName() + "\");\n";
			source += "\t\tif (rs.wasNull()) {\n";
			source += "\t\t\tdata" + i + " = null;\n";
			source += "\t\t}\n";
			source += "\t\tset" + capFirst(column.getName()) + "(data" + i + ");\n";
			i += 1;
		}
		source += "\t}\n";
		
		return source;
	}
	
	// this function is to deal with any strings that get placed into SQL queries,
	// it deals with string containing ' by changing them to ''
	private String stringHack()
	{
		String source = "";
		
		source += "\tprivate static String stringHack(String str) {\n";
		source += "\t\treturn str.replace(\"'\", \"''\").replace(\"\\\\\", \"\\\\\\\\\");\n";
		source += "\t}\n";
		
		return source;
	}
	
	private String getTableName(Collection<Table> tables, String name)
	{
		for (Table table : tables)
		{
			if (table.getName().equalsIgnoreCase(name))
			{
				return table.getName();
			}
		}
		System.err.println("Could not find table name: " + name);
		return null;
	}
	
	private String capFirst(String str)
	{
		return str.substring(0, 1).toUpperCase() + str.substring(1);
	}
}
