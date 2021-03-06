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
    VALUES(5, "DCNSGA_II_DE", "DCNSGA_II_DE", "DCNSGA_II_DE algorithm", "./DEA4AD/trunk/algorithm/DCNSGA_II_DE");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(6, "DCPICMOA_DE", "DCPICMOA_DE", "DCPICMOA_DE algorithm", "./DEA4AD/trunk/algorithm/DCPICMOA_DE");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(7, "differentialevolution_qs", "differentialevolution_qs", "differentialevolution_qs algorithm", "./DEA4AD/trunk/algorithm/differentialevolution_qs");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(8, "eADE", "eADE", "eADE algorithm", "./DEA4AD/trunk/algorithm/eADE");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(9, "Orthogonaldesign", "Orthogonaldesign", "Orthogonaldesign algorithm", "./DEA4AD/trunk/algorithm/Orthogonaldesign");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(10, "PSO", "PSO", "PSO algorithm", "./DEA4AD/trunk/algorithm/PSO");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, algPath) 
    VALUES(11, "Simple_GA", "Simple_GA", "Simple_GA algorithm", "./DEA4AD/trunk/algorithm/Simple_GA");

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
    VALUES(5, "cone_spiral", "cone_spiral Antenna", "./images/cone_spiral.png", "helical wire cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/cone_spiral");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(6, "feko_spiral_300_400", "feko_spiral_300_400 Antenna", "./images/feko_spiral_300_400.png", "helical wire feko_spiral_300_400 Antenna Problem", "./DEA4AD/trunk/problem/feko_spiral_300_400");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(7, "helical", "helical Antenna", "./images/antenna.png", "helical Antenna Problem", "./DEA4AD/trunk/problem/helical_antenna");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(8, "Helix_Missile_feko", "Helix_Missile_feko Antenna", "./images/Helix_Missile_feko.png", "helical wire Helix_Missile_feko Antenna Problem", "./DEA4AD/trunk/problem/Helix_Missile_feko");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(9, "hfss_four_dioples", "hfss_four_dioples Antenna", "./images/hfss_four_dioples.png", "patch hfss_four_dioples Antenna Problem", "./DEA4AD/trunk/problem/hfss_four_dioples");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(10, "hfss_printed", "hfss_printed Antenna", "./images/antenna.png", "hfss_printed Antenna Problem", "./DEA4AD/trunk/problem/hfss_printed");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(11, "Log_spiral", "Log_spiral Antenna", "./images/Log_spiral.png", "patch Log_spiral Antenna Problem", "./DEA4AD/trunk/problem/Log_spiral");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(12, "patch", "patch Antenna", "./images/patch.png", "patch Antenna Problem", "./DEA4AD/trunk/problem/patch");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(13, "plane_spiral", "plane_spiral Antenna", "./images/antenna.png", "plane_spiral Antenna Problem", "./DEA4AD/trunk/problem/plane_spiral_antenna");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(14, "Polygon_cone_spiral", "Polygon_cone_spiral Antenna", "./images/Polygon_cone_spiral.png", "helical Polygon_cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/Polygon_cone_spiral");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(15, "reducedrank", "reducedrank Antenna", "./images/antenna.png", "reducedrank Antenna Problem", "./DEA4AD/trunk/problem/reducedrank");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(16,"robust", "robust Antenna", "./images/antenna.png", "robust Antenna Problem", "./DEA4AD/trunk/problem/robust");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(17, "robustC", "robustC Antenna", "./images/robustC.png", "patch robustC Antenna Problem", "./DEA4AD/trunk/problem/robustC");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(18, "sidelobes", "sidelobes Antenna", "./images/antenna.png", "sidelobes Antenna Problem", "./DEA4AD/trunk/problem/sidelobes");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(19, "sidelobes_2", "sidelobes_2 Antenna", "./images/antenna.png", "sidelobes_2 Antenna Problem", "./DEA4AD/trunk/problem/sidelobes_2");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(20, "sidelobes_3", "sidelobes_3 Antenna", "./images/antenna.png", "sidelobes_3 Antenna Problem", "./DEA4AD/trunk/problem/sidelobes_3");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(21, "SingleTwistedWires", "SingleTwistedWires Antenna", "./images/antenna.png", "wire SingleTwistedWires Antenna Problem", "./DEA4AD/trunk/problem/SingleTwistedWires");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(22, "SingleTwistedWires_feko", "SingleTwistedWires_feko Antenna", "./images/SingleTwistedWires_feko.png", " wire SingleTwistedWires_feko Antenna Problem", "./DEA4AD/trunk/problem/SingleTwistedWires_feko");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(23, "spherical_spiral", "spherical_spiral Antenna", "./images/spherical_spiral.png", "helical wire spherical_spiral Antenna Problem", "./DEA4AD/trunk/problem/spherical_spiral");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(24, "spiral_antenna_nec", "spiral_antenna_nec Antenna", "./images/antenna.png", "spiral_antenna_nec Antenna Problem", "./DEA4AD/trunk/problem/spiral_antenna_nec");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(25, "TDRS_C", "TDRS_C Antenna", "./images/antenna.png", "TDRS_C Antenna Problem", "./DEA4AD/trunk/problem/TDRS_C");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(26, "Template_Problem_feko", "Template_Problem_feko Antenna", "./images/Template_Problem_feko.png", "wire Template_Problem_feko Antenna Problem", "./DEA4AD/trunk/problem/Template_Problem_feko");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(27, "Wave_cone_spiral", "Wave_cone_spiral Antenna", "./images/Wave_cone_spiral.png", "helical Wave_cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/Wave_cone_spiral");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, proPath) 
    VALUES(28, "Wire_Missile_feko", "Wire_Missile_feko Antenna", "./images/Wire_Missile_feko.png", "wire Wire_Missile_feko Antenna Problem", "./DEA4AD/trunk/problem/Wire_Missile_feko");

CREATE TABLE algtopro(
    mId INT PRIMARY KEY NOT NULL,
    pId INT NOT NULL,
    aId INT NOT NULL
);
INSERT INTO algtopro(mId, pId, aId) VALUES(1, 1, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(2, 1, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(3, 1, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(4, 1, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(5, 2, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(6, 2, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(7, 2, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(8, 2, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(9, 3, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(10, 3, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(11, 3, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(12, 4, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(13, 4, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(14, 5, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(15, 6, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(16, 7, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(17, 8, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(18, 9, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(19, 10, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(20, 11, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(21, 12, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(22, 13, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(23, 14, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(24, 15, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(25, 16, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(26, 17, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(27, 18, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(28, 19, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(29, 20, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(30, 21, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(31, 22, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(32, 22, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(33, 22, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(34, 22, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(35, 23, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(36, 24, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(37, 24, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(38, 24, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(39, 24, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(40, 25, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(41, 25, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(42, 25, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(43, 25, 8);