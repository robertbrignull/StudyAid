package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class Proof {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_proofID;
		private SetState m_proofID_set;
		private String m_proofName;
		private SetState m_proofName_set;
		private String m_proofText;
		private SetState m_proofText_set;
		private Integer m_proofForFact;
		private SetState m_proofForFact_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_proofID_set = SetState.Unset;
			m_proofName_set = SetState.Unset;
			m_proofText_set = SetState.Unset;
			m_proofForFact_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition proofID(Integer p_proofID) {
			m_proofID = p_proofID;
			m_proofID_set = (p_proofID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition proofIDNot(Integer p_proofID) {
			m_proofID = p_proofID;
			m_proofID_set = (p_proofID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition proofIDLessThan(Integer p_proofID) {
			m_proofID = p_proofID;
			m_proofID_set = (p_proofID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition proofIDMoreThan(Integer p_proofID) {
			m_proofID = p_proofID;
			m_proofID_set = (p_proofID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition proofName(String p_proofName) {
			m_proofName = p_proofName;
			m_proofName_set = (p_proofName == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition proofNameNot(String p_proofName) {
			m_proofName = p_proofName;
			m_proofName_set = (p_proofName == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition proofNameLessThan(String p_proofName) {
			m_proofName = p_proofName;
			m_proofName_set = (p_proofName == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition proofNameMoreThan(String p_proofName) {
			m_proofName = p_proofName;
			m_proofName_set = (p_proofName == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition proofText(String p_proofText) {
			m_proofText = p_proofText;
			m_proofText_set = (p_proofText == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition proofTextNot(String p_proofText) {
			m_proofText = p_proofText;
			m_proofText_set = (p_proofText == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition proofTextLessThan(String p_proofText) {
			m_proofText = p_proofText;
			m_proofText_set = (p_proofText == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition proofTextMoreThan(String p_proofText) {
			m_proofText = p_proofText;
			m_proofText_set = (p_proofText == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition proofForFact(Integer p_proofForFact) {
			m_proofForFact = p_proofForFact;
			m_proofForFact_set = (p_proofForFact == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition proofForFactNot(Integer p_proofForFact) {
			m_proofForFact = p_proofForFact;
			m_proofForFact_set = (p_proofForFact == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition proofForFactLessThan(Integer p_proofForFact) {
			m_proofForFact = p_proofForFact;
			m_proofForFact_set = (p_proofForFact == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition proofForFactMoreThan(Integer p_proofForFact) {
			m_proofForFact = p_proofForFact;
			m_proofForFact_set = (p_proofForFact == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_proofID_set == SetState.Equal) {
				sql += " and proofID = " + (m_proofID == null ? "null" : m_proofID.toString());
			} else if (m_proofID_set == SetState.NotEqual) {
				sql += " and proofID <> " + (m_proofID == null ? "null" : m_proofID.toString());
			} else if (m_proofID_set == SetState.Null) {
				sql += " and proofID is null";
			} else if (m_proofID_set == SetState.NotNull) {
				sql += " and proofID is not null";
			} else if (m_proofID_set == SetState.LessThan) {
				sql += " and proofID < " + (m_proofID == null ? "null" : m_proofID.toString());
			} else if (m_proofID_set == SetState.MoreThan) {
				sql += " and proofID > " + (m_proofID == null ? "null" : m_proofID.toString());
			}
			
			if (m_proofName_set == SetState.Equal) {
				sql += " and proofName = " + (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
			} else if (m_proofName_set == SetState.NotEqual) {
				sql += " and proofName <> " + (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
			} else if (m_proofName_set == SetState.Null) {
				sql += " and proofName is null";
			} else if (m_proofName_set == SetState.NotNull) {
				sql += " and proofName is not null";
			} else if (m_proofName_set == SetState.LessThan) {
				sql += " and proofName < " + (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
			} else if (m_proofName_set == SetState.MoreThan) {
				sql += " and proofName > " + (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
			}
			
			if (m_proofText_set == SetState.Equal) {
				sql += " and proofText = " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
			} else if (m_proofText_set == SetState.NotEqual) {
				sql += " and proofText <> " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
			} else if (m_proofText_set == SetState.Null) {
				sql += " and proofText is null";
			} else if (m_proofText_set == SetState.NotNull) {
				sql += " and proofText is not null";
			} else if (m_proofText_set == SetState.LessThan) {
				sql += " and proofText < " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
			} else if (m_proofText_set == SetState.MoreThan) {
				sql += " and proofText > " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
			}
			
			if (m_proofForFact_set == SetState.Equal) {
				sql += " and proofForFact = " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
			} else if (m_proofForFact_set == SetState.NotEqual) {
				sql += " and proofForFact <> " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
			} else if (m_proofForFact_set == SetState.Null) {
				sql += " and proofForFact is null";
			} else if (m_proofForFact_set == SetState.NotNull) {
				sql += " and proofForFact is not null";
			} else if (m_proofForFact_set == SetState.LessThan) {
				sql += " and proofForFact < " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
			} else if (m_proofForFact_set == SetState.MoreThan) {
				sql += " and proofForFact > " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
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
	
	
	
	public Proof(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_proofID;
	private String m_proofName;
	private String m_proofText;
	private Integer m_proofForFact;
	private Fact m_proofForFact_record;
	
	
	
	public Integer getProofID() {
		return m_proofID;
	}
	
	public void setProofID(Integer p_proofID) {
		m_proofID = p_proofID;
	}
	
	public String getProofName() {
		return m_proofName;
	}
	
	public void setProofName(String p_proofName) {
		m_proofName = p_proofName;
	}
	
	public String getProofText() {
		return m_proofText;
	}
	
	public void setProofText(String p_proofText) {
		m_proofText = p_proofText;
	}
	
	public Fact getProofForFactRecord() throws SQLException {
		if (m_proofForFact_record == null) {
			Fact.Condition condition = new Fact.Condition();
			condition.factID(m_proofForFact);
			List<Fact> list = Fact.get(m_conn, condition);
			if (list.size() == 0) {
				m_proofForFact_record = null;
			} else {
				m_proofForFact_record = list.get(0);
			}
		}
		return m_proofForFact_record;
	}
	
	public Integer getProofForFact () {
		return m_proofForFact;
	}
	
	public void setProofForFact(Integer p_proofForFact) {
		m_proofForFact = p_proofForFact;
		m_proofForFact_record = null;
	}
	
	public void setProofForFactRecord(Fact p_proofForFact) {
		m_proofForFact_record = p_proofForFact;
		if (p_proofForFact != null) {
			m_proofForFact = p_proofForFact.getFactID();
		}
	}
	
	
	
	
	public List<Dependency> getDependencysWithDependentTo() throws SQLException {
		Dependency.Condition cond = new Dependency.Condition();
		cond.dependentTo(m_proofID);
		return Dependency.get(m_conn, cond);
	}
	
	public List<TestResult> getTestResultsWithTestResultProof() throws SQLException {
		TestResult.Condition cond = new TestResult.Condition();
		cond.testResultProof(m_proofID);
		return TestResult.get(m_conn, cond);
	}
	
	
	
	
	public void loadFromProof(Proof obj) {
		m_conn = obj.m_conn;
		m_proofID = obj.m_proofID;
		m_proofName = obj.m_proofName;
		m_proofText = obj.m_proofText;
		m_proofForFact = obj.m_proofForFact;
		m_proofForFact_record = null;
	}
	
	
	
	public static List<Proof> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<Proof>();
		}
		
		String sql = "select * from Proof where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<Proof> list = new Vector<Proof>();
		
		while (rs.next()) {
		Proof obj = new Proof(conn);
			
			Integer data0 = rs.getInt("proofID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setProofID(data0);
			
			String data1 = rs.getString("proofName");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setProofName(data1);
			
			String data2 = rs.getString("proofText");
			if (rs.wasNull()) {
				data2 = null;
			}
			obj.setProofText(data2);
			
			Integer data3 = rs.getInt("proofForFact");
			if (rs.wasNull()) {
				data3 = null;
			}
			obj.setProofForFact(data3);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from Proof where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into Proof (";
		sql += "proofName";
		sql += ", " + "proofText";
		sql += ", " + "proofForFact";
		sql += ") values (";
		sql += (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
		sql += ", " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
		sql += ", " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_proofID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update Proof set ";
		sql += "proofName = " + (m_proofName == null ? "null" : ("'" + stringHack(m_proofName) + "'"));
		sql += ", " + "proofText = " + (m_proofText == null ? "null" : ("'" + stringHack(m_proofText) + "'"));
		sql += ", " + "proofForFact = " + (m_proofForFact == null ? "null" : m_proofForFact.toString());
		sql += " where (1 = 1)";
		sql += " and proofID = " + (m_proofID == null ? "null" : m_proofID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from Proof where 1 = 1";
		sql += " and proofID = " + (m_proofID == null ? "null" : m_proofID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from Proof where (1 = 1)";
		sql += " and proofID = " + (m_proofID == null ? "null" : m_proofID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("proofID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setProofID(data0);
		
		String data1 = rs.getString("proofName");
		if (rs.wasNull()) {
			data1 = null;
		}
		setProofName(data1);
		
		String data2 = rs.getString("proofText");
		if (rs.wasNull()) {
			data2 = null;
		}
		setProofText(data2);
		
		Integer data3 = rs.getInt("proofForFact");
		if (rs.wasNull()) {
			data3 = null;
		}
		setProofForFact(data3);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}