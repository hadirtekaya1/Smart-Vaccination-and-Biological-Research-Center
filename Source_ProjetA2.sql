CREATE TABLE EXPERIMENTS (
    experiment_id   NUMBER PRIMARY KEY,
    name            VARCHAR2(100) NOT NULL,
    description     CLOB,
    protocol        CLOB,
    status          VARCHAR2(30) CHECK (status IN ('Planned', 'In Progress', 'Completed', 'Analyzed', 'Reported')),
    start_date      DATE,
    end_date        DATE
);
