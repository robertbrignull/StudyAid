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

Integer courseID = Integer.parseInt(request.getParameter("courseID"));
Course course = Course.get(conn, new Course.Condition().courseID(courseID)).get(0);
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
		<script type="text/javascript" src="<%=prefix %>/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
		<script type="text/javascript">
			function displayStatement()
			{
				document.getElementById("displayedStatement").innerHTML = document.getElementById("factStatement").value;
				MathJax.Hub.Queue(["Typeset", MathJax.Hub, "displayedStatement"]);
				
				document.getElementById("displayedStatement").style.display = "block";
				document.getElementById("editableStatement").style.display = "none";
			}
			
			function editStatement()
			{
				document.getElementById("displayedStatement").style.display = "none";
				document.getElementById("editableStatement").style.display = "block";
			}
			
			window.onload = function()
			{
				displayStatement();
			}
		</script>
	</head>
	</head>
	<body>
		<title>StudyAid : <%=course.getCourseName() %> : Add Fact...</title>
		<div class="main">
			<div class="margins">
				<h1>Add fact for <%=course.getCourseName() %></h1>
				<hr/><br/>
				<form name="addFact" action="<%=prefix %>/methods/addFact.jsp" method="get">
					<input type="hidden" name="factForCourse" value="<%=courseID %>"/>
					Fact name: <input type="text" name="factName"/><br/><br/>
					Fact type: <select name="factType">
					<%
					for (FactType factType : FactType.get(conn, null))
					{
						%>
						<option><%=factType.getFactType() %></option>
						<%
					}
					%>
					</select><br/><br/>
					Ordering: <input type="text" name="factOrder"/><br/><br/>
					Statement:<br/>
					<button type="button" onclick="displayStatement()">Display</button>
					<button type="button" onclick="editStatement()">Edit</button>
					<br/><br/>
					<div class="roundedRect" id="displayedStatement"></div>
					<div id="editableStatement"><textArea id="factStatement" name="factStatement" rows="10" cols="70"></textArea></div>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=course.getCourseID() %>')">Cancel</button>
					<button type="submit" style="float: right">Create</button>
				</form>
			</div>
		</div>
	</body>
</html>

