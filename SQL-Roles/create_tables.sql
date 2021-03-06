DROP TABLE IF EXISTS homework CASCADE;
DROP TABLE IF EXISTS mark CASCADE;
DROP TABLE IF EXISTS admin CASCADE;
DROP TABLE IF EXISTS teacher CASCADE;
DROP TABLE IF EXISTS pupil CASCADE;
DROP TABLE IF EXISTS subject CASCADE;
DROP TABLE IF EXISTS grade CASCADE;

CREATE TABLE grade (
    id SERIAL PRIMARY KEY,
    grade_num INTEGER NOT NULL,
    grade_char char(3)
);

CREATE TABLE subject (
    id SERIAL PRIMARY KEY,
    name VARCHAR(128)
);

CREATE TABLE pupil (
    id SERIAL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronimyc VARCHAR(64),
    grade_id INTEGER NOT NULL REFERENCES grade(id),
    login VARCHAR(64) NOT NULL
);

CREATE TABLE teacher (
    id SERIAL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronimyc VARCHAR(64),
    login VARCHAR(64) NOT NULL
);

CREATE TABLE admin (
    id SERIAL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronimyc VARCHAR(64),
    login VARCHAR(64) NOT NULL
);

CREATE TABLE mark (
    id SERIAL PRIMARY KEY,
    pupil_id INTEGER NOT NULL REFERENCES pupil(id),
    mark INTEGER NOT NULL CHECK(mark > 0),
    subject_id INTEGER NOT NULL REFERENCES subject(id),
    mark_date DATE NOT NULL,
    teacher_id INTEGER NOT NULL
);

CREATE TABLE homework (
    id SERIAL PRIMARY KEY,
    teacher_id INTEGER NOT NULL REFERENCES teacher(id),
    subject_id INTEGER NOT NULL REFERENCES subject(id),
    grade_id INTEGER NOT NULL REFERENCES grade(id),
    homework_date DATE NOT NULL,
    homework_text TEXT NOT NULL
);

ALTER TABLE mark ENABLE ROW LEVEL SECURITY;
ALTER TABLE homework ENABLE ROW LEVEL SECURITY;

ALTER TABLE admin ENABLE ROW LEVEL SECURITY;
ALTER TABLE teacher ENABLE ROW LEVEL SECURITY;
ALTER TABLE pupil ENABLE ROW LEVEL SECURITY;