package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class TestResult {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_testResultID;
		private SetState m_testResultID_set;
		private Timestamp m_testResultTimestamp;
		private SetState m_testResultTimestamp_set;
		private Integer m_testResultProof;
		private SetState m_testResultProof_set;
		private String m_testResultType;
		private SetState m_testResultType_set;
		private Integer m_testResultCompleted;
		private SetState m_testResultCompleted_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_testResultID_set = SetState.Unset;
			m_testResultTimestamp_set = SetState.Unset;
			m_testResultProof_set = SetState.Unset;
			m_testResultType_set = SetState.Unset;
			m_testResultCompleted_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition testResultID(Integer p_testResultID) {
			m_testResultID = p_testResultID;
			m_testResultID_set = (p_testResultID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testResultIDNot(Integer p_testResultID) {
			m_testResultID = p_testResultID;
			m_testResultID_set = (p_testResultID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testResultIDLessThan(Integer p_testResultID) {
			m_testResultID = p_testResultID;
			m_testResultID_set = (p_testResultID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testResultIDMoreThan(Integer p_testResultID) {
			m_testResultID = p_testResultID;
			m_testResultID_set = (p_testResultID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition testResultTimestamp(Timestamp p_testResultTimestamp) {
			m_testResultTimestamp = p_testResultTimestamp;
			m_testResultTimestamp_set = (p_testResultTimestamp == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testResultTimestampNot(Timestamp p_testResultTimestamp) {
			m_testResultTimestamp = p_testResultTimestamp;
			m_testResultTimestamp_set = (p_testResultTimestamp == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testResultTimestampLessThan(Timestamp p_testResultTimestamp) {
			m_testResultTimestamp = p_testResultTimestamp;
			m_testResultTimestamp_set = (p_testResultTimestamp == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testResultTimestampMoreThan(Timestamp p_testResultTimestamp) {
			m_testResultTimestamp = p_testResultTimestamp;
			m_testResultTimestamp_set = (p_testResultTimestamp == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition testResultProof(Integer p_testResultProof) {
			m_testResultProof = p_testResultProof;
			m_testResultProof_set = (p_testResultProof == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testResultProofNot(Integer p_testResultProof) {
			m_testResultProof = p_testResultProof;
			m_testResultProof_set = (p_testResultProof == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testResultProofLessThan(Integer p_testResultProof) {
			m_testResultProof = p_testResultProof;
			m_testResultProof_set = (p_testResultProof == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testResultProofMoreThan(Integer p_testResultProof) {
			m_testResultProof = p_testResultProof;
			m_testResultProof_set = (p_testResultProof == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition testResultType(String p_testResultType) {
			m_testResultType = p_testResultType;
			m_testResultType_set = (p_testResultType == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testResultTypeNot(String p_testResultType) {
			m_testResultType = p_testResultType;
			m_testResultType_set = (p_testResultType == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testResultTypeLessThan(String p_testResultType) {
			m_testResultType = p_testResultType;
			m_testResultType_set = (p_testResultType == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testResultTypeMoreThan(String p_testResultType) {
			m_testResultType = p_testResultType;
			m_testResultType_set = (p_testResultType == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition testResultCompleted(Integer p_testResultCompleted) {
			m_testResultCompleted = p_testResultCompleted;
			m_testResultCompleted_set = (p_testResultCompleted == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition testResultCompletedNot(Integer p_testResultCompleted) {
			m_testResultCompleted = p_testResultCompleted;
			m_testResultCompleted_set = (p_testResultCompleted == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition testResultCompletedLessThan(Integer p_testResultCompleted) {
			m_testResultCompleted = p_testResultCompleted;
			m_testResultCompleted_set = (p_testResultCompleted == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition testResultCompletedMoreThan(Integer p_testResultCompleted) {
			m_testResultCompleted = p_testResultCompleted;
			m_testResultCompleted_set = (p_testResultCompleted == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_testResultID_set == SetState.Equal) {
				sql += " and testResultID = " + (m_testResultID == null ? "null" : m_testResultID.toString());
			} else if (m_testResultID_set == SetState.NotEqual) {
				sql += " and testResultID <> " + (m_testResultID == null ? "null" : m_testResultID.toString());
			} else if (m_testResultID_set == SetState.Null) {
				sql += " and testResultID is null";
			} else if (m_testResultID_set == SetState.NotNull) {
				sql += " and testResultID is not null";
			} else if (m_testResultID_set == SetState.LessThan) {
				sql += " and testResultID < " + (m_testResultID == null ? "null" : m_testResultID.toString());
			} else if (m_testResultID_set == SetState.MoreThan) {
				sql += " and testResultID > " + (m_testResultID == null ? "null" : m_testResultID.toString());
			}
			
			if (m_testResultTimestamp_set == SetState.Equal) {
				sql += " and testResultTimestamp = " + (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
			} else if (m_testResultTimestamp_set == SetState.NotEqual) {
				sql += " and testResultTimestamp <> " + (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
			} else if (m_testResultTimestamp_set == SetState.Null) {
				sql += " and testResultTimestamp is null";
			} else if (m_testResultTimestamp_set == SetState.NotNull) {
				sql += " and testResultTimestamp is not null";
			} else if (m_testResultTimestamp_set == SetState.LessThan) {
				sql += " and testResultTimestamp < " + (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
			} else if (m_testResultTimestamp_set == SetState.MoreThan) {
				sql += " and testResultTimestamp > " + (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
			}
			
			if (m_testResultProof_set == SetState.Equal) {
				sql += " and testResultProof = " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
			} else if (m_testResultProof_set == SetState.NotEqual) {
				sql += " and testResultProof <> " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
			} else if (m_testResultProof_set == SetState.Null) {
				sql += " and testResultProof is null";
			} else if (m_testResultProof_set == SetState.NotNull) {
				sql += " and testResultProof is not null";
			} else if (m_testResultProof_set == SetState.LessThan) {
				sql += " and testResultProof < " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
			} else if (m_testResultProof_set == SetState.MoreThan) {
				sql += " and testResultProof > " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
			}
			
			if (m_testResultType_set == SetState.Equal) {
				sql += " and testResultType = " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
			} else if (m_testResultType_set == SetState.NotEqual) {
				sql += " and testResultType <> " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
			} else if (m_testResultType_set == SetState.Null) {
				sql += " and testResultType is null";
			} else if (m_testResultType_set == SetState.NotNull) {
				sql += " and testResultType is not null";
			} else if (m_testResultType_set == SetState.LessThan) {
				sql += " and testResultType < " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
			} else if (m_testResultType_set == SetState.MoreThan) {
				sql += " and testResultType > " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
			}
			
			if (m_testResultCompleted_set == SetState.Equal) {
				sql += " and testResultCompleted = " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
			} else if (m_testResultCompleted_set == SetState.NotEqual) {
				sql += " and testResultCompleted <> " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
			} else if (m_testResultCompleted_set == SetState.Null) {
				sql += " and testResultCompleted is null";
			} else if (m_testResultCompleted_set == SetState.NotNull) {
				sql += " and testResultCompleted is not null";
			} else if (m_testResultCompleted_set == SetState.LessThan) {
				sql += " and testResultCompleted < " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
			} else if (m_testResultCompleted_set == SetState.MoreThan) {
				sql += " and testResultCompleted > " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
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
	
	
	
	public TestResult(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_testResultID;
	private Timestamp m_testResultTimestamp;
	private Integer m_testResultProof;
	private Proof m_testResultProof_record;
	private String m_testResultType;
	private TestType m_testResultType_record;
	private Integer m_testResultCompleted;
	
	
	
	public Integer getTestResultID() {
		return m_testResultID;
	}
	
	public void setTestResultID(Integer p_testResultID) {
		m_testResultID = p_testResultID;
	}
	
	public Timestamp getTestResultTimestamp() {
		return m_testResultTimestamp;
	}
	
	public void setTestResultTimestamp(Timestamp p_testResultTimestamp) {
		m_testResultTimestamp = p_testResultTimestamp;
	}
	
	public Proof getTestResultProofRecord() throws SQLException {
		if (m_testResultProof_record == null) {
			Proof.Condition condition = new Proof.Condition();
			condition.proofID(m_testResultProof);
			List<Proof> list = Proof.get(m_conn, condition);
			if (list.size() == 0) {
				m_testResultProof_record = null;
			} else {
				m_testResultProof_record = list.get(0);
			}
		}
		return m_testResultProof_record;
	}
	
	public Integer getTestResultProof () {
		return m_testResultProof;
	}
	
	public void setTestResultProof(Integer p_testResultProof) {
		m_testResultProof = p_testResultProof;
		m_testResultProof_record = null;
	}
	
	public void setTestResultProofRecord(Proof p_testResultProof) {
		m_testResultProof_record = p_testResultProof;
		if (p_testResultProof != null) {
			m_testResultProof = p_testResultProof.getProofID();
		}
	}
	
	public TestType getTestResultTypeRecord() throws SQLException {
		if (m_testResultType_record == null) {
			TestType.Condition condition = new TestType.Condition();
			condition.testType(m_testResultType);
			List<TestType> list = TestType.get(m_conn, condition);
			if (list.size() == 0) {
				m_testResultType_record = null;
			} else {
				m_testResultType_record = list.get(0);
			}
		}
		return m_testResultType_record;
	}
	
	public String getTestResultType () {
		return m_testResultType;
	}
	
	public void setTestResultType(String p_testResultType) {
		m_testResultType = p_testResultType;
		m_testResultType_record = null;
	}
	
	public void setTestResultTypeRecord(TestType p_testResultType) {
		m_testResultType_record = p_testResultType;
		if (p_testResultType != null) {
			m_testResultType = p_testResultType.getTestType();
		}
	}
	
	public Integer getTestResultCompleted() {
		return m_testResultCompleted;
	}
	
	public void setTestResultCompleted(Integer p_testResultCompleted) {
		m_testResultCompleted = p_testResultCompleted;
	}
	
	
	
	
	
	
	
	public void loadFromTestResult(TestResult obj) {
		m_conn = obj.m_conn;
		m_testResultID = obj.m_testResultID;
		m_testResultTimestamp = obj.m_testResultTimestamp;
		m_testResultProof = obj.m_testResultProof;
		m_testResultProof_record = null;
		m_testResultType = obj.m_testResultType;
		m_testResultType_record = null;
		m_testResultCompleted = obj.m_testResultCompleted;
	}
	
	
	
	public static List<TestResult> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<TestResult>();
		}
		
		String sql = "select * from TestResult where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<TestResult> list = new Vector<TestResult>();
		
		while (rs.next()) {
		TestResult obj = new TestResult(conn);
			
			Integer data0 = rs.getInt("testResultID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setTestResultID(data0);
			
			Timestamp data1 = rs.getTimestamp("testResultTimestamp");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setTestResultTimestamp(data1);
			
			Integer data2 = rs.getInt("testResultProof");
			if (rs.wasNull()) {
				data2 = null;
			}
			obj.setTestResultProof(data2);
			
			String data3 = rs.getString("testResultType");
			if (rs.wasNull()) {
				data3 = null;
			}
			obj.setTestResultType(data3);
			
			Integer data4 = rs.getInt("testResultCompleted");
			if (rs.wasNull()) {
				data4 = null;
			}
			obj.setTestResultCompleted(data4);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from TestResult where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into TestResult (";
		sql += "testResultTimestamp";
		sql += ", " + "testResultProof";
		sql += ", " + "testResultType";
		sql += ", " + "testResultCompleted";
		sql += ") values (";
		sql += (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
		sql += ", " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
		sql += ", " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
		sql += ", " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_testResultID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update TestResult set ";
		sql += "testResultTimestamp = " + (m_testResultTimestamp == null ? "null" : ("'" + m_testResultTimestamp.toString().substring(0, 19) + "'"));
		sql += ", " + "testResultProof = " + (m_testResultProof == null ? "null" : m_testResultProof.toString());
		sql += ", " + "testResultType = " + (m_testResultType == null ? "null" : ("'" + stringHack(m_testResultType) + "'"));
		sql += ", " + "testResultCompleted = " + (m_testResultCompleted == null ? "null" : m_testResultCompleted.toString());
		sql += " where (1 = 1)";
		sql += " and testResultID = " + (m_testResultID == null ? "null" : m_testResultID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from TestResult where 1 = 1";
		sql += " and testResultID = " + (m_testResultID == null ? "null" : m_testResultID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from TestResult where (1 = 1)";
		sql += " and testResultID = " + (m_testResultID == null ? "null" : m_testResultID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("testResultID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setTestResultID(data0);
		
		Timestamp data1 = rs.getTimestamp("testResultTimestamp");
		if (rs.wasNull()) {
			data1 = null;
		}
		setTestResultTimestamp(data1);
		
		Integer data2 = rs.getInt("testResultProof");
		if (rs.wasNull()) {
			data2 = null;
		}
		setTestResultProof(data2);
		
		String data3 = rs.getString("testResultType");
		if (rs.wasNull()) {
			data3 = null;
		}
		setTestResultType(data3);
		
		Integer data4 = rs.getInt("testResultCompleted");
		if (rs.wasNull()) {
			data4 = null;
		}
		setTestResultCompleted(data4);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}