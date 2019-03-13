-- TODO revoke role from all users

DROP POLICY IF EXISTS admin_admins ON admin;
DROP POLICY IF EXISTS teacher_admins ON teacher;
DROP POLICY IF EXISTS pupil_admins ON pupil;

DROP POLICY IF EXISTS teacher_teachers ON teacher;
DROP POLICY IF EXISTS pupil_teachers ON pupil;

DROP POLICY IF EXISTS pupil_pupils ON pupil;

DROP POLICY IF EXISTS mark_admins ON mark;
DROP POLICY IF EXISTS homework_admins ON homework;

DROP POLICY IF EXISTS mark_teachers ON mark;
DROP POLICY IF EXISTS homework_teachers ON homework;

DROP POLICY IF EXISTS mark_pupils ON mark;
DROP POLICY IF EXISTS homework_pupils ON homework;

REVOKE ALL ON grade FROM admins;
REVOKE ALL ON subject FROM admins;
REVOKE ALL ON pupil FROM admins;
REVOKE ALL ON teacher FROM admins;
REVOKE ALL ON mark FROM admins;
REVOKE ALL ON homework FROM admins;
REVOKE USAGE ON grade_id_seq FROM admins;
REVOKE USAGE ON homework_id_seq FROM admins;
REVOKE USAGE ON mark_id_seq FROM admins;
REVOKE USAGE ON pupil_id_seq FROM admins;
REVOKE USAGE ON subject_id_seq FROM admins;
REVOKE USAGE ON teacher_id_seq FROM admins;
REVOKE ALL ON FUNCTION add_teacher FROM admins;
REVOKE ALL ON FUNCTION add_pupil FROM admins;
REVOKE ALL ON admin FROM admins;
REVOKE teachers FROM admins;
REVOKE pupils FROM admins;

REVOKE ALL ON grade FROM teachers;
REVOKE ALL ON subject FROM teachers;
REVOKE ALL ON pupil FROM teachers;
REVOKE ALL ON mark FROM teachers;
REVOKE ALL ON homework FROM teachers;
REVOKE ALL ON teacher FROM teachers;
REVOKE USAGE ON mark_id_seq FROM teachers;
REVOKE USAGE ON homework_id_seq FROM teachers;

REVOKE ALL ON mark FROM pupils;
REVOKE ALL ON homework FROM pupils;
REVOKE ALL ON grade FROM pupils;
REVOKE ALL ON subject FROM pupils;
REVOKE ALL ON pupil FROM pupils;

DROP ROLE IF EXISTS admins;
DROP ROLE IF EXISTS teachers;
DROP ROLE IF EXISTS pupils;

CREATE ROLE admins WITH CREATEROLE;
CREATE ROLE teachers;
CREATE ROLE pupils;

GRANT teachers TO admins WITH ADMIN OPTION;
GRANT pupils TO admins WITH ADMIN OPTION;
GRANT ALL ON grade TO admins;
GRANT ALL ON subject TO admins;
GRANT ALL ON pupil TO admins;
GRANT ALL ON teacher TO admins;
GRANT ALL ON mark TO admins;
GRANT ALL ON homework TO admins;
GRANT SELECT ON admin TO admins;
GRANT USAGE ON grade_id_seq TO admins;
GRANT USAGE ON homework_id_seq TO admins;
GRANT USAGE ON mark_id_seq TO admins;
GRANT USAGE ON pupil_id_seq TO admins;
GRANT USAGE ON subject_id_seq TO admins;
GRANT USAGE ON teacher_id_seq TO admins;
GRANT ALL ON FUNCTION add_teacher TO admins;
GRANT ALL ON FUNCTION add_pupil TO admins;

GRANT SELECT ON grade TO teachers;
GRANT SELECT ON subject TO teachers;
GRANT SELECT ON pupil TO teachers;
GRANT SELECT, INSERT, UPDATE, DELETE ON mark TO teachers;
GRANT SELECT, INSERT, UPDATE, DELETE ON homework TO teachers;
GRANT SELECT ON teacher TO teachers;
GRANT USAGE ON mark_id_seq TO teachers;
GRANT USAGE ON homework_id_seq TO teachers;

GRANT SELECT ON mark TO pupils;
GRANT SELECT ON homework TO pupils;
GRANT SELECT ON grade TO pupils;
GRANT SELECT ON subject TO pupils;
GRANT SELECT ON pupil TO pupils;

CREATE POLICY mark_admins ON mark TO admins USING(true) WITH CHECK(true);
CREATE POLICY homework_admins ON homework TO admins USING(true) WITH CHECK(true);

CREATE POLICY mark_teachers ON mark TO teachers USING((SELECT teacher.login FROM teacher WHERE teacher.id = mark.teacher_id) = current_user);
CREATE POLICY homework_teachers ON homework TO teachers USING((SELECT teacher.login FROM teacher WHERE teacher.id = homework.teacher_id) = current_user);

CREATE POLICY mark_pupils ON mark TO pupils USING((SELECT pupil.login FROM pupil WHERE pupil.id = mark.pupil_id) = current_user) WITH CHECK(false);
CREATE POLICY homework_pupils ON homework TO pupils USING((SELECT pupil.grade_id FROM pupil WHERE pupil.login = current_user) = homework.grade_id) WITH CHECK(false);

CREATE POLICY admin_admins ON admin TO admins USING(login = current_user) WITH CHECK(false);
CREATE POLICY teacher_admins ON teacher TO admins USING(true) WITH CHECK(true);
CREATE POLICY pupil_admins ON pupil TO admins USING(true) WITH CHECK(true);

CREATE POLICY teacher_teachers ON teacher TO teachers USING(login = current_user) WITH CHECK(false);
CREATE POLICY pupil_teachers ON pupil TO teachers USING(true) WITH CHECK(false);

CREATE POLICY pupil_pupils ON pupil TO pupils USING(login = current_user) WITH CHECK(false);