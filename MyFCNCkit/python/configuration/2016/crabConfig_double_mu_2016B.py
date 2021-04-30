#from CRABClient.UserUtilities import config, getUsernameFromSiteDB
#print getUsernameFromSiteDB()
from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Data_double_mu_2016B_94X_new'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
#config.JobType.generator = 'lhe'
config.JobType.psetName = 'patRefSel_Data16_cfg.py'
config.JobType.pyCfgParams = ['runOnMC=0','runOnMiniAOD=1']
#config.JobType.inputFiles = ['dynlo.lhe']
config.Data.ignoreLocality = True
#config.Site.ignoreCrab3blacklist = True
config.Site.whitelist = ['T2_*']
#config.Site.whitelist = ['T2_TW_NCHC']
#config.Site.whitelist = ['T3_TW_NTU_HEP']
#config.Site.blacklist = ['T2_IT_Legnaro']

config.Data.inputDataset = '/DoubleMuon/Run2016B-17Jul2018_ver2-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt'
#config.Data.runRange = '272007-275376'
config.Data.outLFNDirBase = '/store/user/chunting/'
config.Data.publication = False
config.Data.outputDatasetTag = 'MC_TT_TZ3L'

#config.Data.splitting = 'EventBased'
#JOB_WALLTIME = 8*3600
#TIME_PER_EVENT = 12.91
##config.Data.unitsPerJob = int(JOB_WALLTIME / TIME_PER_EVENT)
#config.Data.unitsPerJob = 5000
#NJOBS = 20
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
#config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 1
#config.Data.inputDBS = 'global'
#config.Data.splitting = 'LumiBased'
#config.Data.unitsPerJob = 20
#config.Data.totalUnits = 1000
#config.Data.lumiMask = 'Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
#config.Data.runRange = '272760-273017' # '193093-194075'
#272760, 272761, 272762, 272774, 272775, 272776, 272782, 272783, 272784, 272785, 272786, 272798, 272811, 272812, 272815, 272816, 272818, 272827, 272828, 272930, 272936, 273013, 273017
#config.Data.outLFNDirBase = '/store/user/%s/mc1/' % (getUsernameFromSiteDB())
#config.Data.outLFNDirBase = '/store/user/yuanchao/mc/'
#config.Data.publication = True
#config.Data.publication = False
#config.Data.outputDatasetTag = 'MC_LHE-1'
#config.Data.outputDatasetTag = 'MC_TT_TZ3L'

#config.Site.storageSite = 'T3_TW_NTU_HEP'
config.Site.storageSite = 'T2_TW_NCHC'
