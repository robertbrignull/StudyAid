package Scaffold;

import java.io.BufferedInputStream;
import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.util.Collection;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.Unmarshaller;

import Scaffold.Routine.Routine;
import Scaffold.Table.Table;
import Scaffold.Table.Column;
import Scaffold.SQLServer.SQLServerConnection;
import Scaffold.MySQL.MySQLConnection;

public class Scaffold
{
	public static void main(String[] args)
	{
		if(args.length < 6)
    	{
    		System.err.println("Usage: java Scaffold host port username password dbName outputDir");
    		System.exit(1);
    	}
		
		String host = args[0];
    	String port = args[1];
    	String username = args[2];
    	String password = args[3];
    	String dbName = args[4];
    	String outputDir = args[5];
    	
    	DBConnection conn = new MySQLConnection();
    	
    	conn.openConnection(host, port, username, password, dbName);
    	Collection<Routine> routines = conn.getRoutines();
    	Collection<Table> tables = conn.getTables();
    	
    	BufferedWriter out = null;
    	try
    	{
			(new File(outputDir + "/" + dbName)).mkdirs();
    		out = new BufferedWriter(new FileWriter(outputDir + "/" + dbName + "/" + dbName + ".java"));
    		
    		out.write("package " + dbName + ";\n\n");
    		
    		out.write("import java.util.Map;\n");
    		out.write("import java.util.HashMap;\n");
    		out.write("import java.sql.Connection;\n");
    		out.write("import java.sql.SQLException;\n");
    		out.write("import java.sql.PreparedStatement;\n");
    		out.write("import java.sql.CallableStatement;\n");
    		out.write("import java.sql.Types;\n");
    		out.write("import java.sql.ResultSet;\n");
    		out.write("import java.sql.Timestamp;\n\n");
    		
    		out.write("public class " + dbName + " {\n\n");
    		
    		for (Routine routine : routines)
    		{
    			out.write(routine.getSource());
    		}
    		
    		out.write("}");
	    	out.flush();
			out.close();
			
			
			
			for (Table table : tables)
			{
				(new File(outputDir + "/" + dbName + "/Tables")).mkdirs();
				out = new BufferedWriter(new FileWriter(outputDir + "/" + dbName + "/Tables/" + table.getName() + ".java"));
				
				out.write("package " + dbName + ".Tables;\n\n");
				
				out.write("import java.util.List;\n");
				out.write("import java.util.Vector;\n");
				out.write("import java.sql.Connection;\n");
				out.write("import java.sql.SQLException;\n");
				out.write("import java.sql.PreparedStatement;\n");
				out.write("import java.sql.ResultSet;\n");
				out.write("import java.sql.Timestamp;\n\n");

				out.write("public class " + table.getName() + " {\n");
				
				out.write(table.getSource(tables));

				out.write("}");
	    		
		    	out.flush();
				out.close();
			}
    	}
    	catch (IOException e)
    	{
    		e.printStackTrace();
    	}
    	
    	conn.closeConnection();
	}
	
	// this function is to combat ResultSets and PreparedStatements
	// that have a setInt function rather than setInteger
	public static String nameHack(String str)
	{
		if ("Integer".equalsIgnoreCase(str))
		{
			return "Int";
		}
		
		return str;
	}
}
