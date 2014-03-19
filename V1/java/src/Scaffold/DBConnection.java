package Scaffold;

import java.util.Collection;

import Scaffold.Routine.Routine;
import Scaffold.Table.Table;

public interface DBConnection
{
	public void openConnection(String host, String port, String username, String password, String dbName);
	
	public void closeConnection();
	
	public Collection<Routine> getRoutines();
	
	public Collection<Table> getTables();
}
