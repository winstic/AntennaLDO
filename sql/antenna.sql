CREATE TABLE algorithm(
    aId         INT         PRIMARY KEY NOT NULL, 
    aName       TEXT        NOT NULL,
    aEngName    TEXT        NOT NULL,
    aInfo       TEXT,
    algPath     TEXT
);

INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(1, "DCMODE_DE_1C", "DCMODE_DE_1C", "DCMODE_DE_1C algorithm", "./DEA4AD/trunk/algorithm/DCMODE_DE_1C");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(2, "DCMODE_DE_1C_Share", "DCMODE_DE_1C_Share", "DCMODE_DE_1C_Share algorithm", "./DEA4AD/trunk/algorithm/DCMODE_DE_1C_Share");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(3, "DCMOEA_Econvex_1C", "DCMOEA_Econvex_1C", "DCMOEA_Econvex_1C algorithm", "./DEA4AD/trunk/algorithm/DCMOEA_Econvex_1C");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(4, "DCMOEA_Econvex_1C_Share", "DCMOEA_Econvex_1C_Share", "DCMOEA_Econvex_1C_Share algorithm", "./DEA4AD/trunk/algorithm/DCMOEA_Econvex_1C_Share");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(5, "differentialevolution_qs", "differentialevolution_qs", "differentialevolution_qs algorithm", "./DEA4AD/trunk/algorithm/differentialevolution_qs");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(6, "GPModel", "GPModel", "GPModel algorithm", "./DEA4AD/trunk/algorithm/GPModel");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(7, "Orthogonaldesign", "Orthogonaldesign", "Orthogonaldesign algorithm", "./DEA4AD/trunk/algorithm/Orthogonaldesign");

CREATE TABLE antennaProblem(
    pId         INT         PRIMARY KEY NOT NULL,
    pName       TEXT        NOT NULL,
    pEngName    TEXT        NOT NULL,
    pModelPath  TEXT,
    pInfo       TEXT,
    proPath     TEXT
);
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(1, "hfss_dual_loop", "hfss_dual_loop Antenna", "./images/hfss_dual_loop.png", "patch hfss_dual_loop Antenna Problem", "./DEA4AD/trunk/problem/hfss_dual_loop");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(2, "hfss_LADEE_megain", "hfss_LADEE_megain Antenna", "./images/hfss_LADEE_megain.png", "wire hfss_LADEE_megain Antenna Problem", "./DEA4AD/trunk/problem/hfss_LADEE_megain");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(3, "hfss_mobile_antenna", "hfss_mobile_antenna Antenna", "./images/hfss_mobile_antenna.png", "hfss_mobile_antenna Antenna Problem", "./DEA4AD/trunk/problem/hfss_mobile_antenna");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(4, "wifiAntenna", "wifiAntenna Antenna", "./images/wifiAntenna.png", "patch wifiAntenna Antenna Problem", "./DEA4AD/trunk/problem/wifiAntenna");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(5, "GP_WiFiAntenna", "GP_WiFiAntenna Antenna", "./images/antenna.png", "patch wifiAntenna Antenna Problem", "./DEA4AD/trunk/problem/GP_WiFiAntenna");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(6, "hfss_four_dioples", "hfss_four_dioples Antenna", "./images/hfss_four_dioples.png", "patch hfss_four_dioples Antenna Problem", "./DEA4AD/trunk/problem/hfss_four_dioples");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(7, "hfss_spiral", "hfss_spiral Antenna", "./images/antenna.png", "patch hfss_spiral Antenna Problem", "./DEA4AD/trunk/problem/hfss_spiral");

CREATE TABLE algtopro(
    mId INT PRIMARY KEY NOT NULL,
    pId INT NOT NULL,
    aId INT NOT NULL
);
INSERT INTO algtopro(mId, pId, aId) VALUES(1, 1, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(2, 2, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(3, 3, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(4, 4, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(5, 5, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(6, 6, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(7, 1, 1);
INSERT INTO algtopro(mId, pId, aId) VALUES(8, 4, 1);
INSERT INTO algtopro(mId, pId, aId) VALUES(9, 1, 2);
INSERT INTO algtopro(mId, pId, aId) VALUES(10, 1, 3);
INSERT INTO algtopro(mId, pId, aId) VALUES(11, 1, 4);
INSERT INTO algtopro(mId, pId, aId) VALUES(12, 7, 7);


