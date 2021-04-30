
#
# This file contains the Top PAG reference selection work-flow for mu + jets analysis.
# as defined in
# https://twiki.cern.ch/twiki/bin/view/CMS/TWikiTopRefEventSel#mu_jets_Channel
#
# Command line arguments:
# - standard command line arguments as defined in FWCore.ParameterSet.VarParsing.VarParsing( 'standard' )
#   + 'maxEvents' (int , default: -1)
# - 'runOnMC'          (bool, default: True ): decide if run on MC or real data
# - 'runOnMiniAOD'     (bool, default: True ): decide if run on miniAOD or AOD input
# - 'useElecEAIsoCorr' (bool, default: True ): decide, if EA (rho) or Delta beta corrections are used for electron isolation
# - 'useCalibElec'     (bool, default: False): decide, if electron re-calibration using regression energies is used
# - 'addTriggerMatch'  (bool, default: True ): decide, if trigger objects are matched to signal muons
#


import sys

import FWCore.ParameterSet.Config as cms


# Command line parsing

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ( 'standard' )
options.register( 'runOnMC'         , True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, 'decide, if run on MC or real data' )
options.register( 'runOnMiniAOD'    , True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, 'decide, if run on miniAOD or AOD input' )
# parsing command line arguments
if( hasattr( sys, 'argv' ) ):
  if( len( sys.argv ) > 2 ):
    print 'Parsing command line arguments:'
  for args in sys.argv :
    arg = args.split(',')
    for val in arg:
      val = val.split( '=' )
      if( len( val ) == 2 ):
        print 'Setting "', val[0], '" to:', val[1]
        setattr( options, val[0], val[1] )


process = cms.Process( 'USER' )
#process.Tracer = cms.Service( "Tracer" )


### ======================================================================== ###
###                                                                          ###
###                                 Constants                                ###
###                            (user job steering)                           ###
###                                                                          ###
### ======================================================================== ###


from TopQuarkAnalysis.Configuration.patRefSel_refMuJets import *

inputFiles = []


### Selection steps
# If a step is switched off here, its results will still be available in the coreespondinng TriggerResults of this process.

selectEvents = 'pGoodVertex'

# Step 0
triggerSelectionData = 'HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v*'
triggerSelectionMC = 'HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v*'

electronCut = electronGsfCut

bTagSrc = 'selectedJets'

runOnMC      = options.runOnMC
runOnMiniAOD = options.runOnMiniAOD

# maximum number of events
#maxEvents = options.maxEvents
maxEvents = -1
#maxEvents = 6000

### Conditions

# GlobalTags
globalTagMC   = '94X_mcRun2_asymptotic_v3'
globalTagData = '94X_dataRun2_v10'

### Output

# output file
outputFile = 'patRefSel_fcnc.root'

# event frequency of Fwk report
fwkReportEvery = max( 1000, ( maxEvents / 1000 ) )

# switch for 'TrigReport'/'TimeReport' at job end
wantSummary = True


### ======================================================================== ###
###                                                                          ###
###                              End of constants                            ###
###                            (user job steering)                           ###
###                                                                          ###
### ======================================================================== ###


triggerSelection       = triggerSelectionData
triggerObjectSelection = triggerObjectSelectionData
if runOnMC:
  triggerSelection       = triggerSelectionMC
  triggerObjectSelection = triggerObjectSelectionMC


###
### Basic configuration
###


process.load( "TopQuarkAnalysis.Configuration.patRefSel_basics_cff" )
process.MessageLogger.cerr.FwkReport.reportEvery = fwkReportEvery
process.options.wantSummary = wantSummary

process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
if runOnMC:
    process.GlobalTag.globaltag = globalTagMC
else:
    process.GlobalTag.globaltag = globalTagData
###
### Input configuration
###

if len( inputFiles ) == 0:
  if runOnMiniAOD:
    if runOnMC:
      from PhysicsTools.PatAlgos.patInputFiles_cff import filesRelValTTbarPileUpMINIAODSIM
      inputFiles = filesRelValTTbarPileUpMINIAODSIM
    else:
      from PhysicsTools.PatAlgos.patInputFiles_cff import filesRelValSingleMuMINIAOD
      inputFiles = filesRelValSingleMuMINIAOD
  else:
    if runOnMC:
      from PhysicsTools.PatAlgos.patInputFiles_cff import filesRelValProdTTbarAODSIM
      inputFiles = filesRelValProdTTbarAODSIM
    else:
      from PhysicsTools.PatAlgos.patInputFiles_cff import filesSingleMuRECO # not available at CERN
      inputFiles = filesSingleMuRECO

process.load( "TopQuarkAnalysis.Configuration.patRefSel_inputModule_cfi" )

process.source.fileNames = cms.untracked.vstring("file:./DY_2016.root")
#process.source.fileNames = cms.untracked.vstring("root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/10000/0893B9A4-FD41-E811-AF47-008CFAC94284.root")

process.maxEvents.input  = maxEvents


###
### PAT configuration
###

if not runOnMiniAOD:
  process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )



###
### Output configuration
###

#process.load( "TopQuarkAnalysis.Configuration.patRefSel_outputModule_cff" )
## output file name
#process.out.fileName = outputFile
#from TopQuarkAnalysis.Configuration.patRefSel_eventContent_cff import refMuJets_eventContent
#process.out.outputCommands += refMuJets_eventContent
#if runOnMiniAOD:
#  from TopQuarkAnalysis.Configuration.patRefSel_eventContent_cff import miniAod_eventContent
#  process.out.outputCommands += miniAod_eventContent
#else:
#  from TopQuarkAnalysis.Configuration.patRefSel_eventContent_cff import aod_eventContent
#  process.out.outputCommands += aod_eventContent
## clear event selection
#process.out.SelectEvents.SelectEvents = cms.vstring( selectEvents )


###
### Selection configuration
###

# Individual steps

from PhysicsTools.SelectorUtils.tools.vid_id_tools import * 
dataFormat = DataFormat.AOD

if runOnMiniAOD:
  dataFormat = DataFormat.MiniAOD

# define which IDs we want to produce
switchOnVIDElectronIdProducer( process, dataFormat )

my_id_modules = [ #'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
                  #'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff'
                  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff'
                 ]

#add them to the VID producer
for idmod in my_id_modules:
  setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)

# Step 4

#------------------------------JetToolBox---------------------------------#
#from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
#
#listBtagDiscriminators = [
#        'pfCombinedInclusiveSecondaryVertexV2BJetTags',
#        'pfCombinedMVAV2BJetTags',
#        #Deep CSV
#        'pfDeepCSVJetTags:probb',
#        'pfDeepCSVJetTags:probbb',
#        'pfDeepCSVJetTags:probc',
#        'pfDeepCSVJetTags:probudsg',
#        ##Deep CSV summary
#        'pfDeepCSVDiscriminatorsJetTags:BvsAll',
#        'pfDeepCSVDiscriminatorsJetTags:CvsB',
#        'pfDeepCSVDiscriminatorsJetTags:CvsL'
#]
#ak4Cut='pt > 25 && abs(eta) < 5.'
#
#jetToolbox( process, 'ak4', 'ak4chs', 'edmOut',
#            runOnMC = True,
#            addQGTagger = True,
#            addPUJetID         = True,
#            bTagDiscriminators = listBtagDiscriminators,
#            Cut = ak4Cut )
#
#JetToolBoxSequence = cms.Sequence( process.jetTask )
#setattr( process, 'JetToolBoxSequence', JetToolBoxSequence)
#-----------------------------------------------------------------------#

# Settings for MET bug fixing
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD (
        process,
        isData = False,
        fixEE2017 = True,
        fixEE2017Params = {'userawPt': True, 'ptThreshold':50.0, 'minEtaThreshold':2.65, 'maxEtaThreshold': 3.139},
        postfix = "ModifiedMET"
        )

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(
        process,
        runVID=True, #saves CPU time by not needlessly re-running VID
        runEnergyCorrections = False,
        era='2016-Legacy'
        )
process.bugfixingSequence = cms.Sequence()
#process.bugfixingSequence += process.egammaPostRecoSeq
#process.bugfixingSequence += process.fullPatMetSequenceModifiedMET
from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
        DataEra = cms.string('2016BtoH'),
        UseJetEMPt = cms.bool(False),
        PrefiringRateSystematicUncty = cms.double(0.2),
        SkipWarnings = False
        )
process.externalCorrectionSequence = cms.Sequence()
process.externalCorrectionSequence += process.prefiringweight

process.fcncKit = cms.EDAnalyzer('MyFCNCkit',
      MCtag = cms.untracked.bool(False),
      muonlabel = cms.InputTag("slimmedMuons"),
      eleclabel = cms.InputTag("slimmedElectrons"),
#      eleidveto = cms.InputTag('cutBasedElectronID-Fall17-94X-V1-veto'),
#      eleidloose = cms.InputTag("cutBasedElectronID-Fall17-94X-V1-loose"),
#      eleidmedium = cms.InputTag("cutBasedElectronID-Fall17-94X-V1-medium"),
#      eleidtight = cms.InputTag("cutBasedElectronID-Fall17-94X-V1-tight"),
      eleidveto = cms.string('cutBasedElectronID-Fall17-94X-V2-veto'),
      eleidloose = cms.string("cutBasedElectronID-Fall17-94X-V2-loose"),
      eleidmedium = cms.string("cutBasedElectronID-Fall17-94X-V2-medium"),
      eleidtight = cms.string("cutBasedElectronID-Fall17-94X-V2-tight"),
      convlabel = cms.InputTag("reducedEgamma:reducedConversions"),
      #pfjetlabel= cms.InputTag("selectedPatJetsAK4PFCHS"),
      pfjetlabel= cms.InputTag("slimmedJets"),
      metlabel  = cms.InputTag("slimmedMETs"),
      #metlabel  = cms.InputTag("slimmedMETsModifiedMET"),
      genlabel  = cms.InputTag("prunedGenParticles"),
      hltlabel  = cms.InputTag("TriggerResults::HLT"),
      pathltlabel = cms.InputTag("patTriggerEvent"),
      offlinePVlabel = cms.InputTag("offlineSlimmedPrimaryVertices"),
      offlineBSlabel = cms.InputTag("offlineBeamSpot"),
      genevtlabel = cms.InputTag("generator"),
      gtdigilabel = cms.InputTag("gtDigis"),
      rhoIsoInputLabel = cms.InputTag("fixedGridRhoFastjetAll"),
      puInfoLabel = cms.InputTag("slimmedAddPileupInfo"),
      mettriggersrc = cms.InputTag("TriggerResults","","PAT"),
      lhesrc     = cms.InputTag('externalLHEProducer'),
      lherunsrc  = cms.InputTag('externalLHEProducer'),
      prefwgtsrc = cms.InputTag('prefiringweight:nonPrefiringProb'),
      prefwgtupsrc = cms.InputTag('prefiringweight:nonPrefiringProbUp'),
      prefwgtdownsrc = cms.InputTag('prefiringweight:nonPrefiringProbDown')
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string('TTHWcZpWZ_test.root')
      )

process.sfcncKit       = cms.Sequence( #process.sTrigger
                                      #process.sStandAloneEventCleaning
                                       process.egmGsfElectronIDSequence
                                      *process.egammaPostRecoSeq
                                      *process.externalCorrectionSequence
                                      #* process.bugfixingSequence
                                      #* process.JetToolBoxSequence
                                      * process.fcncKit
                                     )

process.pfcncKit       = cms.Path( process.sfcncKit )


process.outpath = cms.EndPath()

