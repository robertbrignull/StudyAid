<%@ page import = "java.util.*" %>
<%@ page import = "java.sql.*" %>

<%@ page import = "StudyAid.Tables.*" %>

<%
Connection conn = (Connection) session.getAttribute("conn");
String prefix = (String) session.getAttribute("prefix");

if (conn == null) {
	Class.forName("com.mysql.jdbc.Driver").newInstance();
	String connectionURL = "jdbc:mysql://localhost:3306/StudyAid";
	conn = DriverManager.getConnection(connectionURL, "root", "mysql");
	session.setAttribute("conn", conn);
}

if (prefix == null) {
	prefix = "http://localhost:8080/StudyAid";
	session.setAttribute("prefix", prefix);
}
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
	</head>
	<body>
		<title>StudyAid : Courses...</title>
		<div class="main">
			<div class="margins">
				<h1>Courses!</h1>
				<hr/>
				<table class="paddedTable" width="100%">
					<%
					List<FactType> factTypes = FactType.get(conn, null);
					
					List<Course> courses = Course.get(conn, null);
					Collections.sort(courses, new Comparator<Course>() {
						public int compare(Course c1, Course c2) {
							return c1.getCourseName().compareTo(c2.getCourseName());
						}
					});
					
					for (Course course : courses)
					{
						Map<String, Integer> numFacts = new HashMap<String, Integer>();
						Map<String, Integer> numProofs = new HashMap<String, Integer>();
						
						for (FactType factType : factTypes)
						{
							List<Fact> facts = Fact.get(conn, new Fact.Condition().factForCourse(course.getCourseID()).factType(factType.getFactType()));
							numFacts.put(factType.getFactType(), facts.size());
							
							int n = 0;
							for (Fact fact : facts)
							{
								if (fact.getProofsWithProofForFact().size() > 0)
								{
									++n;
								}
							}
							numProofs.put(factType.getFactType(), n);
						}
						%>
						<tr>
							<td class="paddedCell" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=course.getCourseID() %>')">
								<h3><%=course.getCourseName() %></h3>
								<table width="100%">
								<%
								for (FactType factType : factTypes)
								{
									%>
									<tr>
										<td width="50%">Number of <%=factType.getFactType() %>s: <%=numFacts.get(factType.getFactType()) %></td>
										<%
										if (factType.getFactTypeCanHaveProof() != 0)
										{
											%>
											<td>Number proven: <%=numProofs.get(factType.getFactType()) %></td>
											<%
										}
										%>
									</tr>
									<%
								}
								%>
								</table>
							</td>
						</tr>
						<%
					}
					%>
				</table>
				<button type="button" style="float: right" onmousedown="goToPage(event, '<%=prefix %>/forms/addCourse.jsp')">Add course...</button>
				<br/>
			</div>
		</div>
	</body>
</html>
