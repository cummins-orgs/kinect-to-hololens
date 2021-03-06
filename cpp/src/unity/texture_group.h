#pragma once

#include <memory>
#include <d3d11.h>
#include "kh_trvl.h"
#include "channel_texture.h"
#include "depth_texture.h"

struct TextureGroup
{
public:
    // Color and depth texture sizes.
    int width;
    int height;

    // Instances of classes for Direct3D textures.
    std::unique_ptr<kh::ChannelTexture> y_texture{nullptr};
    std::unique_ptr<kh::ChannelTexture> u_texture{nullptr};
    std::unique_ptr<kh::ChannelTexture> v_texture{nullptr};
    std::unique_ptr<kh::DepthTexture> depth_texture{nullptr};

    // Unity connects Unity textures to Direct3D textures through creating Unity textures binded to these texture views.
    ID3D11ShaderResourceView* y_texture_view{nullptr};
    ID3D11ShaderResourceView* u_texture_view{nullptr};
    ID3D11ShaderResourceView* v_texture_view{nullptr};
    ID3D11ShaderResourceView* depth_texture_view{nullptr};

    // These variables get set in the main thread of Unity, then gets assigned to textures in the render thread of Unity.
    kh::FFmpegFrame ffmpeg_frame{nullptr};
    std::unique_ptr<kh::TrvlDecoder> depth_decoder;
    std::vector<short> depth_pixels;
};

void texture_group_init(ID3D11Device* device);
void texture_group_update(ID3D11Device* device, ID3D11DeviceContext* device_context);