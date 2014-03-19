package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class TestType {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private String m_testType;
		private SetState m_testType_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_testType_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition testType(String p_testType) {
			m_testType = p_testType;
			m_testType_set = (p_testType == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testTypeNot(String p_testType) {
			m_testType = p_testType;
			m_testType_set = (p_testType == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testTypeLessThan(String p_testType) {
			m_testType = p_testType;
			m_testType_set = (p_testType == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testTypeMoreThan(String p_testType) {
			m_testType = p_testType;
			m_testType_set = (p_testType == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		
		
		
		public Condition or(Condition condition) {
			alternatives.add(condition);
			return this;
		}
		public Condition and(Condition condition) {
			requirements.add(condition);
			return this;
		}
		
		
		
		public String getWhereClause() {
			String sql = "(((1 = 1)";
			if (m_testType_set == SetState.Equal) {
				sql += " and testType = " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
			} else if (m_testType_set == SetState.NotEqual) {
				sql += " and testType <> " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
			} else if (m_testType_set == SetState.Null) {
				sql += " and testType is null";
			} else if (m_testType_set == SetState.NotNull) {
				sql += " and testType is not null";
			} else if (m_testType_set == SetState.LessThan) {
				sql += " and testType < " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
			} else if (m_testType_set == SetState.MoreThan) {
				sql += " and testType > " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
			}
			
			sql += ")";
			
			for (Condition condition : requirements) {
				sql += " and " + condition.getWhereClause();
			}
			
			if (alternatives.size() > 0) {
				sql += " and (";
				boolean first = true;
				for (Condition condition : alternatives) {
					if (!first) {
						sql += " or ";
					}
					first = false;
					sql += condition.getWhereClause();
				}
				sql += ")";
			}
			sql += ")";
			return sql;
		}
	}
	
	
	
	public TestType(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private String m_testType;
	
	
	
	public String getTestType() {
		return m_testType;
	}
	
	public void setTestType(String p_testType) {
		m_testType = p_testType;
	}
	
	
	
	
	public List<TestResult> getTestResultsWithTestResultType() throws SQLException {
		TestResult.Condition cond = new TestResult.Condition();
		cond.testResultType(m_testType);
		return TestResult.get(m_conn, cond);
	}
	
	
	
	
	public void loadFromTestType(TestType obj) {
		m_conn = obj.m_conn;
		m_testType = obj.m_testType;
	}
	
	
	
	public static List<TestType> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<TestType>();
		}
		
		String sql = "select * from TestType where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<TestType> list = new Vector<TestType>();
		
		while (rs.next()) {
		TestType obj = new TestType(conn);
			
			String data0 = rs.getString("testType");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setTestType(data0);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from TestType where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into TestType (";
		sql += ") values (";
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_testType = rs.getString("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update TestType set ";
		sql += " where (1 = 1)";
		sql += " and testType = " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from TestType where 1 = 1";
		sql += " and testType = " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from TestType where (1 = 1)";
		sql += " and testType = " + (m_testType == null ? "null" : ("'" + stringHack(m_testType) + "'"));
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		String data0 = rs.getString("testType");
		if (rs.wasNull()) {
			data0 = null;
		}
		setTestType(data0);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}