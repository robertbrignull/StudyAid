package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class Dependency {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private Integer m_dependencyID;
		private SetState m_dependencyID_set;
		private Integer m_dependentTo;
		private SetState m_dependentTo_set;
		private Integer m_dependentOn;
		private SetState m_dependentOn_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_dependencyID_set = SetState.Unset;
			m_dependentTo_set = SetState.Unset;
			m_dependentOn_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
		}
		
		
		
		public Condition dependencyID(Integer p_dependencyID) {
			m_dependencyID = p_dependencyID;
			m_dependencyID_set = (p_dependencyID == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition dependencyIDNot(Integer p_dependencyID) {
			m_dependencyID = p_dependencyID;
			m_dependencyID_set = (p_dependencyID == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition dependencyIDLessThan(Integer p_dependencyID) {
			m_dependencyID = p_dependencyID;
			m_dependencyID_set = (p_dependencyID == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition dependencyIDMoreThan(Integer p_dependencyID) {
			m_dependencyID = p_dependencyID;
			m_dependencyID_set = (p_dependencyID == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition dependentTo(Integer p_dependentTo) {
			m_dependentTo = p_dependentTo;
			m_dependentTo_set = (p_dependentTo == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition dependentToNot(Integer p_dependentTo) {
			m_dependentTo = p_dependentTo;
			m_dependentTo_set = (p_dependentTo == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition dependentToLessThan(Integer p_dependentTo) {
			m_dependentTo = p_dependentTo;
			m_dependentTo_set = (p_dependentTo == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition dependentToMoreThan(Integer p_dependentTo) {
			m_dependentTo = p_dependentTo;
			m_dependentTo_set = (p_dependentTo == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition dependentOn(Integer p_dependentOn) {
			m_dependentOn = p_dependentOn;
			m_dependentOn_set = (p_dependentOn == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition dependentOnNot(Integer p_dependentOn) {
			m_dependentOn = p_dependentOn;
			m_dependentOn_set = (p_dependentOn == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition dependentOnLessThan(Integer p_dependentOn) {
			m_dependentOn = p_dependentOn;
			m_dependentOn_set = (p_dependentOn == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition dependentOnMoreThan(Integer p_dependentOn) {
			m_dependentOn = p_dependentOn;
			m_dependentOn_set = (p_dependentOn == null) ? SetState.Unset : SetState.MoreThan;
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
			if (m_dependencyID_set == SetState.Equal) {
				sql += " and dependencyID = " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
			} else if (m_dependencyID_set == SetState.NotEqual) {
				sql += " and dependencyID <> " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
			} else if (m_dependencyID_set == SetState.Null) {
				sql += " and dependencyID is null";
			} else if (m_dependencyID_set == SetState.NotNull) {
				sql += " and dependencyID is not null";
			} else if (m_dependencyID_set == SetState.LessThan) {
				sql += " and dependencyID < " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
			} else if (m_dependencyID_set == SetState.MoreThan) {
				sql += " and dependencyID > " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
			}
			
			if (m_dependentTo_set == SetState.Equal) {
				sql += " and dependentTo = " + (m_dependentTo == null ? "null" : m_dependentTo.toString());
			} else if (m_dependentTo_set == SetState.NotEqual) {
				sql += " and dependentTo <> " + (m_dependentTo == null ? "null" : m_dependentTo.toString());
			} else if (m_dependentTo_set == SetState.Null) {
				sql += " and dependentTo is null";
			} else if (m_dependentTo_set == SetState.NotNull) {
				sql += " and dependentTo is not null";
			} else if (m_dependentTo_set == SetState.LessThan) {
				sql += " and dependentTo < " + (m_dependentTo == null ? "null" : m_dependentTo.toString());
			} else if (m_dependentTo_set == SetState.MoreThan) {
				sql += " and dependentTo > " + (m_dependentTo == null ? "null" : m_dependentTo.toString());
			}
			
			if (m_dependentOn_set == SetState.Equal) {
				sql += " and dependentOn = " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
			} else if (m_dependentOn_set == SetState.NotEqual) {
				sql += " and dependentOn <> " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
			} else if (m_dependentOn_set == SetState.Null) {
				sql += " and dependentOn is null";
			} else if (m_dependentOn_set == SetState.NotNull) {
				sql += " and dependentOn is not null";
			} else if (m_dependentOn_set == SetState.LessThan) {
				sql += " and dependentOn < " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
			} else if (m_dependentOn_set == SetState.MoreThan) {
				sql += " and dependentOn > " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
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
	
	
	
	public Dependency(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private Integer m_dependencyID;
	private Integer m_dependentTo;
	private Proof m_dependentTo_record;
	private Integer m_dependentOn;
	private Fact m_dependentOn_record;
	
	
	
	public Integer getDependencyID() {
		return m_dependencyID;
	}
	
	public void setDependencyID(Integer p_dependencyID) {
		m_dependencyID = p_dependencyID;
	}
	
	public Proof getDependentToRecord() throws SQLException {
		if (m_dependentTo_record == null) {
			Proof.Condition condition = new Proof.Condition();
			condition.proofID(m_dependentTo);
			List<Proof> list = Proof.get(m_conn, condition);
			if (list.size() == 0) {
				m_dependentTo_record = null;
			} else {
				m_dependentTo_record = list.get(0);
			}
		}
		return m_dependentTo_record;
	}
	
	public Integer getDependentTo () {
		return m_dependentTo;
	}
	
	public void setDependentTo(Integer p_dependentTo) {
		m_dependentTo = p_dependentTo;
		m_dependentTo_record = null;
	}
	
	public void setDependentToRecord(Proof p_dependentTo) {
		m_dependentTo_record = p_dependentTo;
		if (p_dependentTo != null) {
			m_dependentTo = p_dependentTo.getProofID();
		}
	}
	
	public Fact getDependentOnRecord() throws SQLException {
		if (m_dependentOn_record == null) {
			Fact.Condition condition = new Fact.Condition();
			condition.factID(m_dependentOn);
			List<Fact> list = Fact.get(m_conn, condition);
			if (list.size() == 0) {
				m_dependentOn_record = null;
			} else {
				m_dependentOn_record = list.get(0);
			}
		}
		return m_dependentOn_record;
	}
	
	public Integer getDependentOn () {
		return m_dependentOn;
	}
	
	public void setDependentOn(Integer p_dependentOn) {
		m_dependentOn = p_dependentOn;
		m_dependentOn_record = null;
	}
	
	public void setDependentOnRecord(Fact p_dependentOn) {
		m_dependentOn_record = p_dependentOn;
		if (p_dependentOn != null) {
			m_dependentOn = p_dependentOn.getFactID();
		}
	}
	
	
	
	
	
	
	
	public void loadFromDependency(Dependency obj) {
		m_conn = obj.m_conn;
		m_dependencyID = obj.m_dependencyID;
		m_dependentTo = obj.m_dependentTo;
		m_dependentTo_record = null;
		m_dependentOn = obj.m_dependentOn;
		m_dependentOn_record = null;
	}
	
	
	
	public static List<Dependency> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<Dependency>();
		}
		
		String sql = "select * from Dependency where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<Dependency> list = new Vector<Dependency>();
		
		while (rs.next()) {
		Dependency obj = new Dependency(conn);
			
			Integer data0 = rs.getInt("dependencyID");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setDependencyID(data0);
			
			Integer data1 = rs.getInt("dependentTo");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setDependentTo(data1);
			
			Integer data2 = rs.getInt("dependentOn");
			if (rs.wasNull()) {
				data2 = null;
			}
			obj.setDependentOn(data2);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from Dependency where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into Dependency (";
		sql += "dependentTo";
		sql += ", " + "dependentOn";
		sql += ") values (";
		sql += (m_dependentTo == null ? "null" : m_dependentTo.toString());
		sql += ", " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_dependencyID = rs.getInt("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update Dependency set ";
		sql += "dependentTo = " + (m_dependentTo == null ? "null" : m_dependentTo.toString());
		sql += ", " + "dependentOn = " + (m_dependentOn == null ? "null" : m_dependentOn.toString());
		sql += " where (1 = 1)";
		sql += " and dependencyID = " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from Dependency where 1 = 1";
		sql += " and dependencyID = " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from Dependency where (1 = 1)";
		sql += " and dependencyID = " + (m_dependencyID == null ? "null" : m_dependencyID.toString());
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		Integer data0 = rs.getInt("dependencyID");
		if (rs.wasNull()) {
			data0 = null;
		}
		setDependencyID(data0);
		
		Integer data1 = rs.getInt("dependentTo");
		if (rs.wasNull()) {
			data1 = null;
		}
		setDependentTo(data1);
		
		Integer data2 = rs.getInt("dependentOn");
		if (rs.wasNull()) {
			data2 = null;
		}
		setDependentOn(data2);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}