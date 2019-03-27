source 'https://github.com/CocoaPods/Specs.git'

platform :ios, '9.0'

inhibit_all_warnings!
use_frameworks!

target :MDRecordSDK do
    pod 'MMFrameworks', :path => './MMFramework', :subspecs => ['Eta', 'MMFoundation']
    pod 'MMVideoSDK', :path => './'
    #pod 'MetalPetal', '1.1.2'
    pod 'GPUImage', :git => 'https://github.com/NaichuanYang/GPUImage.git', :commit => '3ba128277babc67048e10c5269694aebaa8bf581'
    pod 'Toast', '~> 4.0.0'
    pod 'MBProgressHUD', '~> 1.1.0'
    pod 'MJRefresh'
    pod 'SDWebImage'
    pod 'SDWebImage/WebP'
    pod 'Masonry'
    pod 'pop'
    pod 'YYImage'
    pod 'ReactiveCocoa', '2.5'
#    pod 'ZipArchive'
end

post_install do |installer|
    installer.pods_project.targets.each do |target|
        
        target.build_configurations.each do |config|
            config.build_settings['CLANG_WARN_DOCUMENTATION_COMMENTS'] = 'NO'
            config.build_settings['ENABLE_BITCODE'] = 'NO'
        end
    end
end


