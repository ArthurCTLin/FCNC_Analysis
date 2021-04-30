from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'TT_FCNC_aTleptonic_kappa_zct_2017_94X_new'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'patRefSel_MC17_cfg.py'
config.JobType.pyCfgParams = ['runOnMC=1','runOnMiniAOD=1']
config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_*']

config.Data.inputDataset = '/TT_FCNC-T2ZJ_aTleptonic_ZToll_kappa_zct-MadGraph5-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.outLFNDirBase = '/store/user/chunting/'
config.Data.publication = False
config.Data.outputDatasetTag = 'MC_TT_TZ3L'
config.Site.storageSite = 'T2_TW_NCHC'
