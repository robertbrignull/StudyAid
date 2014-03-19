package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class Course {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_courseID;
		private SetState m_courseID_set;
		private String m_courseName;
		private SetState m_courseName_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_courseID_set = SetState.Unset;
			m_courseName_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition courseID(Integer p_courseID) {
			m_courseID = p_courseID;
			m_courseID_set = (p_courseID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition courseIDNot(Integer p_courseID) {
			m_courseID = p_courseID;
			m_courseID_set = (p_courseID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition courseIDLessThan(Integer p_courseID) {
			m_courseID = p_courseID;
			m_courseID_set = (p_courseID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition courseIDMoreThan(Integer p_courseID) {
			m_courseID = p_courseID;
			m_courseID_set = (p_courseID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition courseName(String p_courseName) {
			m_courseName = p_courseName;
			m_courseName_set = (p_courseName == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition courseNameNot(String p_courseName) {
			m_courseName = p_courseName;
			m_courseName_set = (p_courseName == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition courseNameLessThan(String p_courseName) {
			m_courseName = p_courseName;
			m_courseName_set = (p_courseName == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition courseNameMoreThan(String p_courseName) {
			m_courseName = p_courseName;
			m_courseName_set = (p_courseName == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_courseID_set == SetState.Equal) {
				sql += " and courseID = " + (m_courseID == null ? "null" : m_courseID.toString());
			} else if (m_courseID_set == SetState.NotEqual) {
				sql += " and courseID <> " + (m_courseID == null ? "null" : m_courseID.toString());
			} else if (m_courseID_set == SetState.Null) {
				sql += " and courseID is null";
			} else if (m_courseID_set == SetState.NotNull) {
				sql += " and courseID is not null";
			} else if (m_courseID_set == SetState.LessThan) {
				sql += " and courseID < " + (m_courseID == null ? "null" : m_courseID.toString());
			} else if (m_courseID_set == SetState.MoreThan) {
				sql += " and courseID > " + (m_courseID == null ? "null" : m_courseID.toString());
			}
			
			if (m_courseName_set == SetState.Equal) {
				sql += " and courseName = " + (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
			} else if (m_courseName_set == SetState.NotEqual) {
				sql += " and courseName <> " + (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
			} else if (m_courseName_set == SetState.Null) {
				sql += " and courseName is null";
			} else if (m_courseName_set == SetState.NotNull) {
				sql += " and courseName is not null";
			} else if (m_courseName_set == SetState.LessThan) {
				sql += " and courseName < " + (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
			} else if (m_courseName_set == SetState.MoreThan) {
				sql += " and courseName > " + (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
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
	
	
	
	public Course(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_courseID;
	private String m_courseName;
	
	
	
	public Integer getCourseID() {
		return m_courseID;
	}
	
	public void setCourseID(Integer p_courseID) {
		m_courseID = p_courseID;
	}
	
	public String getCourseName() {
		return m_courseName;
	}
	
	public void setCourseName(String p_courseName) {
		m_courseName = p_courseName;
	}
	
	
	
	
	public List<Fact> getFactsWithFactForCourse() throws SQLException {
		Fact.Condition cond = new Fact.Condition();
		cond.factForCourse(m_courseID);
		return Fact.get(m_conn, cond);
	}
	
	
	
	
	public void loadFromCourse(Course obj) {
		m_conn = obj.m_conn;
		m_courseID = obj.m_courseID;
		m_courseName = obj.m_courseName;
	}
	
	
	
	public static List<Course> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<Course>();
		}
		
		String sql = "select * from Course where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<Course> list = new Vector<Course>();
		
		while (rs.next()) {
		Course obj = new Course(conn);
			
			Integer data0 = rs.getInt("courseID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setCourseID(data0);
			
			String data1 = rs.getString("courseName");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setCourseName(data1);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from Course where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into Course (";
		sql += "courseName";
		sql += ") values (";
		sql += (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_courseID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update Course set ";
		sql += "courseName = " + (m_courseName == null ? "null" : ("'" + stringHack(m_courseName) + "'"));
		sql += " where (1 = 1)";
		sql += " and courseID = " + (m_courseID == null ? "null" : m_courseID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from Course where 1 = 1";
		sql += " and courseID = " + (m_courseID == null ? "null" : m_courseID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from Course where (1 = 1)";
		sql += " and courseID = " + (m_courseID == null ? "null" : m_courseID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("courseID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setCourseID(data0);
		
		String data1 = rs.getString("courseName");
		if (rs.wasNull()) {
			data1 = null;
		}
		setCourseName(data1);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}