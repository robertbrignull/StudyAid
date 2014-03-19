package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class Lecturer {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_lecturerID;
		private SetState m_lecturerID_set;
		private String m_lecturerName;
		private SetState m_lecturerName_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_lecturerID_set = SetState.Unset;
			m_lecturerName_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition lecturerID(Integer p_lecturerID) {
			m_lecturerID = p_lecturerID;
			m_lecturerID_set = (p_lecturerID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition lecturerIDNot(Integer p_lecturerID) {
			m_lecturerID = p_lecturerID;
			m_lecturerID_set = (p_lecturerID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition lecturerIDLessThan(Integer p_lecturerID) {
			m_lecturerID = p_lecturerID;
			m_lecturerID_set = (p_lecturerID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition lecturerIDMoreThan(Integer p_lecturerID) {
			m_lecturerID = p_lecturerID;
			m_lecturerID_set = (p_lecturerID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition lecturerName(String p_lecturerName) {
			m_lecturerName = p_lecturerName;
			m_lecturerName_set = (p_lecturerName == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition lecturerNameNot(String p_lecturerName) {
			m_lecturerName = p_lecturerName;
			m_lecturerName_set = (p_lecturerName == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition lecturerNameLessThan(String p_lecturerName) {
			m_lecturerName = p_lecturerName;
			m_lecturerName_set = (p_lecturerName == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition lecturerNameMoreThan(String p_lecturerName) {
			m_lecturerName = p_lecturerName;
			m_lecturerName_set = (p_lecturerName == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_lecturerID_set == SetState.Equal) {
				sql += " and lecturerID = " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
			} else if (m_lecturerID_set == SetState.NotEqual) {
				sql += " and lecturerID <> " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
			} else if (m_lecturerID_set == SetState.Null) {
				sql += " and lecturerID is null";
			} else if (m_lecturerID_set == SetState.NotNull) {
				sql += " and lecturerID is not null";
			} else if (m_lecturerID_set == SetState.LessThan) {
				sql += " and lecturerID < " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
			} else if (m_lecturerID_set == SetState.MoreThan) {
				sql += " and lecturerID > " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
			}
			
			if (m_lecturerName_set == SetState.Equal) {
				sql += " and lecturerName = " + (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
			} else if (m_lecturerName_set == SetState.NotEqual) {
				sql += " and lecturerName <> " + (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
			} else if (m_lecturerName_set == SetState.Null) {
				sql += " and lecturerName is null";
			} else if (m_lecturerName_set == SetState.NotNull) {
				sql += " and lecturerName is not null";
			} else if (m_lecturerName_set == SetState.LessThan) {
				sql += " and lecturerName < " + (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
			} else if (m_lecturerName_set == SetState.MoreThan) {
				sql += " and lecturerName > " + (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
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
	
	
	
	public Lecturer(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_lecturerID;
	private String m_lecturerName;
	
	
	
	public Integer getLecturerID() {
		return m_lecturerID;
	}
	
	public void setLecturerID(Integer p_lecturerID) {
		m_lecturerID = p_lecturerID;
	}
	
	public String getLecturerName() {
		return m_lecturerName;
	}
	
	public void setLecturerName(String p_lecturerName) {
		m_lecturerName = p_lecturerName;
	}
	
	
	
	
	
	
	
	public void loadFromLecturer(Lecturer obj) {
		m_conn = obj.m_conn;
		m_lecturerID = obj.m_lecturerID;
		m_lecturerName = obj.m_lecturerName;
	}
	
	
	
	public static List<Lecturer> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<Lecturer>();
		}
		
		String sql = "select * from Lecturer where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<Lecturer> list = new Vector<Lecturer>();
		
		while (rs.next()) {
		Lecturer obj = new Lecturer(conn);
			
			Integer data0 = rs.getInt("lecturerID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setLecturerID(data0);
			
			String data1 = rs.getString("lecturerName");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setLecturerName(data1);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from Lecturer where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into Lecturer (";
		sql += "lecturerName";
		sql += ") values (";
		sql += (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_lecturerID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update Lecturer set ";
		sql += "lecturerName = " + (m_lecturerName == null ? "null" : ("'" + stringHack(m_lecturerName) + "'"));
		sql += " where (1 = 1)";
		sql += " and lecturerID = " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from Lecturer where 1 = 1";
		sql += " and lecturerID = " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from Lecturer where (1 = 1)";
		sql += " and lecturerID = " + (m_lecturerID == null ? "null" : m_lecturerID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("lecturerID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setLecturerID(data0);
		
		String data1 = rs.getString("lecturerName");
		if (rs.wasNull()) {
			data1 = null;
		}
		setLecturerName(data1);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}