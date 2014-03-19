package StudyAid.Tables;

import java.util.List;
import java.util.Vector;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

public class FactType {
	public static class Condition {
		private static enum SetState {
			Unset, Equal, NotEqual, LessThan, MoreThan, Null, NotNull;
		}
		
		private String m_factType;
		private SetState m_factType_set;
		private String m_factTypeColour;
		private SetState m_factTypeColour_set;
		private Integer m_factTypeCanHaveProof;
		private SetState m_factTypeCanHaveProof_set;
		
		List<Condition> alternatives;
		List<Condition> requirements;
		
		
		
		public Condition() {
			m_factType_set = SetState.Unset;
			m_factTypeColour_set = SetState.Unset;
			m_factTypeCanHaveProof_set = SetState.Unset;
			alternatives = new Vector<Condition>();
			requirements = new Vector<Condition>();
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
		
		public Condition factTypeColour(String p_factTypeColour) {
			m_factTypeColour = p_factTypeColour;
			m_factTypeColour_set = (p_factTypeColour == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factTypeColourNot(String p_factTypeColour) {
			m_factTypeColour = p_factTypeColour;
			m_factTypeColour_set = (p_factTypeColour == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factTypeColourLessThan(String p_factTypeColour) {
			m_factTypeColour = p_factTypeColour;
			m_factTypeColour_set = (p_factTypeColour == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factTypeColourMoreThan(String p_factTypeColour) {
			m_factTypeColour = p_factTypeColour;
			m_factTypeColour_set = (p_factTypeColour == null) ? SetState.Unset : SetState.MoreThan;
			return this;
		}
		
		public Condition factTypeCanHaveProof(Integer p_factTypeCanHaveProof) {
			m_factTypeCanHaveProof = p_factTypeCanHaveProof;
			m_factTypeCanHaveProof_set = (p_factTypeCanHaveProof == null) ? SetState.Null : SetState.Equal;
			return this;
		}
		
		public Condition factTypeCanHaveProofNot(Integer p_factTypeCanHaveProof) {
			m_factTypeCanHaveProof = p_factTypeCanHaveProof;
			m_factTypeCanHaveProof_set = (p_factTypeCanHaveProof == null) ? SetState.NotNull : SetState.NotEqual;
			return this;
		}
		
		public Condition factTypeCanHaveProofLessThan(Integer p_factTypeCanHaveProof) {
			m_factTypeCanHaveProof = p_factTypeCanHaveProof;
			m_factTypeCanHaveProof_set = (p_factTypeCanHaveProof == null) ? SetState.Unset : SetState.LessThan;
			return this;
		}
		
		public Condition factTypeCanHaveProofMoreThan(Integer p_factTypeCanHaveProof) {
			m_factTypeCanHaveProof = p_factTypeCanHaveProof;
			m_factTypeCanHaveProof_set = (p_factTypeCanHaveProof == null) ? SetState.Unset : SetState.MoreThan;
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
			
			if (m_factTypeColour_set == SetState.Equal) {
				sql += " and factTypeColour = " + (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
			} else if (m_factTypeColour_set == SetState.NotEqual) {
				sql += " and factTypeColour <> " + (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
			} else if (m_factTypeColour_set == SetState.Null) {
				sql += " and factTypeColour is null";
			} else if (m_factTypeColour_set == SetState.NotNull) {
				sql += " and factTypeColour is not null";
			} else if (m_factTypeColour_set == SetState.LessThan) {
				sql += " and factTypeColour < " + (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
			} else if (m_factTypeColour_set == SetState.MoreThan) {
				sql += " and factTypeColour > " + (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
			}
			
			if (m_factTypeCanHaveProof_set == SetState.Equal) {
				sql += " and factTypeCanHaveProof = " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
			} else if (m_factTypeCanHaveProof_set == SetState.NotEqual) {
				sql += " and factTypeCanHaveProof <> " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
			} else if (m_factTypeCanHaveProof_set == SetState.Null) {
				sql += " and factTypeCanHaveProof is null";
			} else if (m_factTypeCanHaveProof_set == SetState.NotNull) {
				sql += " and factTypeCanHaveProof is not null";
			} else if (m_factTypeCanHaveProof_set == SetState.LessThan) {
				sql += " and factTypeCanHaveProof < " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
			} else if (m_factTypeCanHaveProof_set == SetState.MoreThan) {
				sql += " and factTypeCanHaveProof > " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
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
	
	
	
	public FactType(Connection p_conn) {
		m_conn = p_conn;
	}
	
	
	
	private Connection m_conn;
	
	public Connection getConn() {
		return m_conn;
	}
	
	
	
	private String m_factType;
	private String m_factTypeColour;
	private Integer m_factTypeCanHaveProof;
	
	
	
	public String getFactType() {
		return m_factType;
	}
	
	public void setFactType(String p_factType) {
		m_factType = p_factType;
	}
	
	public String getFactTypeColour() {
		return m_factTypeColour;
	}
	
	public void setFactTypeColour(String p_factTypeColour) {
		m_factTypeColour = p_factTypeColour;
	}
	
	public Integer getFactTypeCanHaveProof() {
		return m_factTypeCanHaveProof;
	}
	
	public void setFactTypeCanHaveProof(Integer p_factTypeCanHaveProof) {
		m_factTypeCanHaveProof = p_factTypeCanHaveProof;
	}
	
	
	
	
	public List<Fact> getFactsWithFactType() throws SQLException {
		Fact.Condition cond = new Fact.Condition();
		cond.factType(m_factType);
		return Fact.get(m_conn, cond);
	}
	
	
	
	
	public void loadFromFactType(FactType obj) {
		m_conn = obj.m_conn;
		m_factType = obj.m_factType;
		m_factTypeColour = obj.m_factTypeColour;
		m_factTypeCanHaveProof = obj.m_factTypeCanHaveProof;
	}
	
	
	
	public static List<FactType> get(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return new Vector<FactType>();
		}
		
		String sql = "select * from FactType where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		List<FactType> list = new Vector<FactType>();
		
		while (rs.next()) {
		FactType obj = new FactType(conn);
			
			String data0 = rs.getString("factType");
			if (rs.wasNull()) {
				data0 = null;
			}
			obj.setFactType(data0);
			
			String data1 = rs.getString("factTypeColour");
			if (rs.wasNull()) {
				data1 = null;
			}
			obj.setFactTypeColour(data1);
			
			Integer data2 = rs.getInt("factTypeCanHaveProof");
			if (rs.wasNull()) {
				data2 = null;
			}
			obj.setFactTypeCanHaveProof(data2);
		list.add(obj);
		}
		
		return list;
	}
	
	
	
	public static int count(Connection conn, Condition condition) throws SQLException {
		if (conn == null) {
			return 0;
		}
		
		String sql = "select count(*) from FactType where ";
		sql += (condition == null) ? "1 = 1" : condition.getWhereClause();
		
		ResultSet rs = conn.createStatement().executeQuery(sql);
		rs.next();
		
		return rs.getInt(1);
	}
	
	
	
	public void create() throws SQLException {
		String sql = "insert into FactType (";
		sql += "factTypeColour";
		sql += ", " + "factTypeCanHaveProof";
		sql += ") values (";
		sql += (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
		sql += ", " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
		sql += ")";
		
		m_conn.createStatement().executeUpdate(sql);
		
		ResultSet rs = m_conn.createStatement().executeQuery("select last_insert_id() as key_out");
		rs.next();
		m_factType = rs.getString("key_out");
	}
	
	
	
	public void update() throws SQLException {
		String sql = "update FactType set ";
		sql += "factTypeColour = " + (m_factTypeColour == null ? "null" : ("'" + stringHack(m_factTypeColour) + "'"));
		sql += ", " + "factTypeCanHaveProof = " + (m_factTypeCanHaveProof == null ? "null" : m_factTypeCanHaveProof.toString());
		sql += " where (1 = 1)";
		sql += " and factType = " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void delete() throws SQLException {
		String sql = "delete from FactType where 1 = 1";
		sql += " and factType = " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
		
		m_conn.createStatement().executeUpdate(sql);
	}
	
	
	
	public void reload() throws SQLException {
		String sql = "select * from FactType where (1 = 1)";
		sql += " and factType = " + (m_factType == null ? "null" : ("'" + stringHack(m_factType) + "'"));
		
		ResultSet rs = m_conn.createStatement().executeQuery(sql);
		rs.next();
		
		String data0 = rs.getString("factType");
		if (rs.wasNull()) {
			data0 = null;
		}
		setFactType(data0);
		
		String data1 = rs.getString("factTypeColour");
		if (rs.wasNull()) {
			data1 = null;
		}
		setFactTypeColour(data1);
		
		Integer data2 = rs.getInt("factTypeCanHaveProof");
		if (rs.wasNull()) {
			data2 = null;
		}
		setFactTypeCanHaveProof(data2);
	}
	
	
	
	private static String stringHack(String str) {
		return str.replace("'", "''").replace("\\", "\\\\");
	}
	
	
	
}