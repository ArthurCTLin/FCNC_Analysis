from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'DYJetsToLL_M50_2017_94X_new2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'patRefSel_MC17_cfg.py'
config.JobType.pyCfgParams = ['runOnMC=1','runOnMiniAOD=1']
config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_*']

config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/chunting/'
config.Data.publication = False
config.Data.outputDatasetTag = 'MC_TT_TZ3L'
config.Site.storageSite = 'T2_TW_NCHC'
