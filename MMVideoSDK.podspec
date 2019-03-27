#
# Be sure to run `pod lib lint MDRecordAndEdit.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'MMVideoSDK'
  s.version          = '1.0.1'
  s.summary          = 'short videos record and edit'

  s.description      = <<-DESC
    this framework use to record,edit short videos
                       DESC

  s.homepage         = 'https://www.baidu.com/'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'bi.s_fish' => 'sunfeifish@gmail.com' }
  s.source           = { :git => 'https://github.com/cosmos33/MMVideoSDK--iOS.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'

  s.frameworks = 'ARKit', 'AVFoundation', 'CoreVideo', 'CoreMedia', 'CoreAudio', 'CoreML', 'AssetsLibrary', 'Vision', 'CoreML', 'Accelerate', 'Metal', 'MetalKit', 'CoreGraphics'
  s.libraries = 'c++', 'resolv', 'z', 'iconv'

  s.resources = 'VideoSDK/Resource/*'

  s.vendored_frameworks = 'VideoSDK/Framwork/**/*.framework'
  s.pod_target_xcconfig = { 'ENABLE_BITCODE' => '$(inherited) NO', 'OTHER_LDFLAGS' => '$(inherited) -ObjC', 'MTL_LANGUAGE_REVISION' => 'Metal12'}
  
  s.dependency 'GPUImage'
  s.dependency 'MetalPetal', '1.1.2'
  s.dependency 'ZipArchive'
end
