package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class Fact {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_factID;
		private SetState m_factID_set;
		private String m_factName;
		private SetState m_factName_set;
		private String m_factType;
		private SetState m_factType_set;
		private Integer m_factForCourse;
		private SetState m_factForCourse_set;
		private String m_factStatement;
		private SetState m_factStatement_set;
		private Integer m_factOrder;
		private SetState m_factOrder_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_factID_set = SetState.Unset;
			m_factName_set = SetState.Unset;
			m_factType_set = SetState.Unset;
			m_factForCourse_set = SetState.Unset;
			m_factStatement_set = SetState.Unset;
			m_factOrder_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition factID(Integer p_factID) {
			m_factID = p_factID;
			m_factID_set = (p_factID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factIDNot(Integer p_factID) {
			m_factID = p_factID;
			m_factID_set = (p_factID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factIDLessThan(Integer p_factID) {
			m_factID = p_factID;
			m_factID_set = (p_factID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factIDMoreThan(Integer p_factID) {
			m_factID = p_factID;
			m_factID_set = (p_factID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factName(String p_factName) {
			m_factName = p_factName;
			m_factName_set = (p_factName == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factNameNot(String p_factName) {
			m_factName = p_factName;
			m_factName_set = (p_factName == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factNameLessThan(String p_factName) {
			m_factName = p_factName;
			m_factName_set = (p_factName == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factNameMoreThan(String p_factName) {
			m_factName = p_factName;
			m_factName_set = (p_factName == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factType(String p_factType) {
			m_factType = p_factType;
			m_factType_set = (p_factType == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factTypeNot(String p_factType) {
			m_factType = p_factType;
			m_factType_set = (p_factType == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factTypeLessThan(String p_factType) {
			m_factType = p_factType;
			m_factType_set = (p_factType == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factTypeMoreThan(String p_factType) {
			m_factType = p_factType;
			m_factType_set = (p_factType == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factForCourse(Integer p_factForCourse) {
			m_factForCourse = p_factForCourse;
			m_factForCourse_set = (p_factForCourse == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factForCourseNot(Integer p_factForCourse) {
			m_factForCourse = p_factForCourse;
			m_factForCourse_set = (p_factForCourse == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factForCourseLessThan(Integer p_factForCourse) {
			m_factForCourse = p_factForCourse;
			m_factForCourse_set = (p_factForCourse == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factForCourseMoreThan(Integer p_factForCourse) {
			m_factForCourse = p_factForCourse;
			m_factForCourse_set = (p_factForCourse == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factStatement(String p_factStatement) {
			m_factStatement = p_factStatement;
			m_factStatement_set = (p_factStatement == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factStatementNot(String p_factStatement) {
			m_factStatement = p_factStatement;
			m_factStatement_set = (p_factStatement == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factStatementLessThan(String p_factStatement) {
			m_factStatement = p_factStatement;
			m_factStatement_set = (p_factStatement == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factStatementMoreThan(String p_factStatement) {
			m_factStatement = p_factStatement;
			m_factStatement_set = (p_factStatement == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factOrder(Integer p_factOrder) {
			m_factOrder = p_factOrder;
			m_factOrder_set = (p_factOrder == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factOrderNot(Integer p_factOrder) {
			m_factOrder = p_factOrder;
			m_factOrder_set = (p_factOrder == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factOrderLessThan(Integer p_factOrder) {
			m_factOrder = p_factOrder;
			m_factOrder_set = (p_factOrder == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factOrderMoreThan(Integer p_factOrder) {
			m_factOrder = p_factOrder;
			m_factOrder_set = (p_factOrder == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_factID_set == SetState.Equal) {
				sql += " and factID = " + (m_factID == null ? "null" : m_factID.toString());
			} else if (m_factID_set == SetState.NotEqual) {
				sql += " and factID <> " + (m_factID == null ? "null" : m_factID.toString());
			} else if (m_factID_set == SetState.Null) {
				sql += " and factID is null";
			} else if (m_factID_set == SetState.NotNull) {
				sql += " and factID is not null";
			} else if (m_factID_set == SetState.LessThan) {
				sql += " and factID < " + (m_factID == null ? "null" : m_factID.toString());
			} else if (m_factID_set == SetState.MoreThan) {
				sql += " and factID > " + (m_factID == null ? "null" : m_factID.toString());
			}
			
			if (m_factName_set == SetState.Equal) {
				sql += " and factName = " + (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
			} else if (m_factName_set == SetState.NotEqual) {
				sql += " and factName <> " + (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
			} else if (m_factName_set == SetState.Null) {
				sql += " and factName is null";
			} else if (m_factName_set == SetState.NotNull) {
				sql += " and factName is not null";
			} else if (m_factName_set == SetState.LessThan) {
				sql += " and factName < " + (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
			} else if (m_factName_set == SetState.MoreThan) {
				sql += " and factName > " + (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
			}
			
			if (m_factType_set == SetState.Equal) {
				sql += " and factType = " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
			} else if (m_factType_set == SetState.NotEqual) {
				sql += " and factType <> " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
			} else if (m_factType_set == SetState.Null) {
				sql += " and factType is null";
			} else if (m_factType_set == SetState.NotNull) {
				sql += " and factType is not null";
			} else if (m_factType_set == SetState.LessThan) {
				sql += " and factType < " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
			} else if (m_factType_set == SetState.MoreThan) {
				sql += " and factType > " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
			}
			
			if (m_factForCourse_set == SetState.Equal) {
				sql += " and factForCourse = " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
			} else if (m_factForCourse_set == SetState.NotEqual) {
				sql += " and factForCourse <> " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
			} else if (m_factForCourse_set == SetState.Null) {
				sql += " and factForCourse is null";
			} else if (m_factForCourse_set == SetState.NotNull) {
				sql += " and factForCourse is not null";
			} else if (m_factForCourse_set == SetState.LessThan) {
				sql += " and factForCourse < " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
			} else if (m_factForCourse_set == SetState.MoreThan) {
				sql += " and factForCourse > " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
			}
			
			if (m_factStatement_set == SetState.Equal) {
				sql += " and factStatement = " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
			} else if (m_factStatement_set == SetState.NotEqual) {
				sql += " and factStatement <> " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
			} else if (m_factStatement_set == SetState.Null) {
				sql += " and factStatement is null";
			} else if (m_factStatement_set == SetState.NotNull) {
				sql += " and factStatement is not null";
			} else if (m_factStatement_set == SetState.LessThan) {
				sql += " and factStatement < " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
			} else if (m_factStatement_set == SetState.MoreThan) {
				sql += " and factStatement > " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
			}
			
			if (m_factOrder_set == SetState.Equal) {
				sql += " and factOrder = " + (m_factOrder == null ? "null" : m_factOrder.toString());
			} else if (m_factOrder_set == SetState.NotEqual) {
				sql += " and factOrder <> " + (m_factOrder == null ? "null" : m_factOrder.toString());
			} else if (m_factOrder_set == SetState.Null) {
				sql += " and factOrder is null";
			} else if (m_factOrder_set == SetState.NotNull) {
				sql += " and factOrder is not null";
			} else if (m_factOrder_set == SetState.LessThan) {
				sql += " and factOrder < " + (m_factOrder == null ? "null" : m_factOrder.toString());
			} else if (m_factOrder_set == SetState.MoreThan) {
				sql += " and factOrder > " + (m_factOrder == null ? "null" : m_factOrder.toString());
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
	
	
	
	public Fact(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_factID;
	private String m_factName;
	private String m_factType;
	private FactType m_factType_record;
	private Integer m_factForCourse;
	private Course m_factForCourse_record;
	private String m_factStatement;
	private Integer m_factOrder;
	
	
	
	public Integer getFactID() {
		return m_factID;
	}
	
	public void setFactID(Integer p_factID) {
		m_factID = p_factID;
	}
	
	public String getFactName() {
		return m_factName;
	}
	
	public void setFactName(String p_factName) {
		m_factName = p_factName;
	}
	
	public FactType getFactTypeRecord() throws SQLException {
		if (m_factType_record == null) {
			FactType.Condition condition = new FactType.Condition();
			condition.factType(m_factType);
			List<FactType> list = FactType.get(m_conn, condition);
			if (list.size() == 0) {
				m_factType_record = null;
			} else {
				m_factType_record = list.get(0);
			}
		}
		return m_factType_record;
	}
	
	public String getFactType () {
		return m_factType;
	}
	
	public void setFactType(String p_factType) {
		m_factType = p_factType;
		m_factType_record = null;
	}
	
	public void setFactTypeRecord(FactType p_factType) {
		m_factType_record = p_factType;
		if (p_factType != null) {
			m_factType = p_factType.getFactType();
		}
	}
	
	public Course getFactForCourseRecord() throws SQLException {
		if (m_factForCourse_record == null) {
			Course.Condition condition = new Course.Condition();
			condition.courseID(m_factForCourse);
			List<Course> list = Course.get(m_conn, condition);
			if (list.size() == 0) {
				m_factForCourse_record = null;
			} else {
				m_factForCourse_record = list.get(0);
			}
		}
		return m_factForCourse_record;
	}
	
	public Integer getFactForCourse () {
		return m_factForCourse;
	}
	
	public void setFactForCourse(Integer p_factForCourse) {
		m_factForCourse = p_factForCourse;
		m_factForCourse_record = null;
	}
	
	public void setFactForCourseRecord(Course p_factForCourse) {
		m_factForCourse_record = p_factForCourse;
		if (p_factForCourse != null) {
			m_factForCourse = p_factForCourse.getCourseID();
		}
	}
	
	public String getFactStatement() {
		return m_factStatement;
	}
	
	public void setFactStatement(String p_factStatement) {
		m_factStatement = p_factStatement;
	}
	
	public Integer getFactOrder() {
		return m_factOrder;
	}
	
	public void setFactOrder(Integer p_factOrder) {
		m_factOrder = p_factOrder;
	}
	
	
	
	
	public List<Dependency> getDependencysWithDependentOn() throws SQLException {
		Dependency.Condition cond = new Dependency.Condition();
		cond.dependentOn(m_factID);
		return Dependency.get(m_conn, cond);
	}
	
	public List<Proof> getProofsWithProofForFact() throws SQLException {
		Proof.Condition cond = new Proof.Condition();
		cond.proofForFact(m_factID);
		return Proof.get(m_conn, cond);
	}
	
	
	
	
	public void loadFromFact(Fact obj) {
		m_conn = obj.m_conn;
		m_factID = obj.m_factID;
		m_factName = obj.m_factName;
		m_factType = obj.m_factType;
		m_factType_record = null;
		m_factForCourse = obj.m_factForCourse;
		m_factForCourse_record = null;
		m_factStatement = obj.m_factStatement;
		m_factOrder = obj.m_factOrder;
	}
	
	
	
	public static List<Fact> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<Fact>();
		}
		
		String sql = "select * from Fact where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<Fact> list = new Vector<Fact>();
		
		while (rs.next()) {
		Fact obj = new Fact(conn);
			
			Integer data0 = rs.getInt("factID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setFactID(data0);
			
			String data1 = rs.getString("factName");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setFactName(data1);
			
			String data2 = rs.getString("factType");
			if (rs.wasNull()) {
				data2 = null;
			}
			obj.setFactType(data2);
			
			Integer data3 = rs.getInt("factForCourse");
			if (rs.wasNull()) {
				data3 = null;
			}
			obj.setFactForCourse(data3);
			
			String data4 = rs.getString("factStatement");
			if (rs.wasNull()) {
				data4 = null;
			}
			obj.setFactStatement(data4);
			
			Integer data5 = rs.getInt("factOrder");
			if (rs.wasNull()) {
				data5 = null;
			}
			obj.setFactOrder(data5);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from Fact where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into Fact (";
		sql += "factName";
		sql += ", " + "factType";
		sql += ", " + "factForCourse";
		sql += ", " + "factStatement";
		sql += ", " + "factOrder";
		sql += ") values (";
		sql += (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
		sql += ", " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
		sql += ", " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
		sql += ", " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
		sql += ", " + (m_factOrder == null ? "null" : m_factOrder.toString());
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_factID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update Fact set ";
		sql += "factName = " + (m_factName == null ? "null" : ("'" + stringHack(m_factName) + "'"));
		sql += ", " + "factType = " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
		sql += ", " + "factForCourse = " + (m_factForCourse == null ? "null" : m_factForCourse.toString());
		sql += ", " + "factStatement = " + (m_factStatement == null ? "null" : ("'" + stringHack(m_factStatement) + "'"));
		sql += ", " + "factOrder = " + (m_factOrder == null ? "null" : m_factOrder.toString());
		sql += " where (1 = 1)";
		sql += " and factID = " + (m_factID == null ? "null" : m_factID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from Fact where 1 = 1";
		sql += " and factID = " + (m_factID == null ? "null" : m_factID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from Fact where (1 = 1)";
		sql += " and factID = " + (m_factID == null ? "null" : m_factID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("factID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setFactID(data0);
		
		String data1 = rs.getString("factName");
		if (rs.wasNull()) {
			data1 = null;
		}
		setFactName(data1);
		
		String data2 = rs.getString("factType");
		if (rs.wasNull()) {
			data2 = null;
		}
		setFactType(data2);
		
		Integer data3 = rs.getInt("factForCourse");
		if (rs.wasNull()) {
			data3 = null;
		}
		setFactForCourse(data3);
		
		String data4 = rs.getString("factStatement");
		if (rs.wasNull()) {
			data4 = null;
		}
		setFactStatement(data4);
		
		Integer data5 = rs.getInt("factOrder");
		if (rs.wasNull()) {
			data5 = null;
		}
		setFactOrder(data5);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}