#include "VulkanTypeConversions.h"

vk::ImageLayout Backend::ToVulkan(Ping::ImageLayout layout)
{
	switch (layout)
	{
	case Ping::ImageLayout::Undefined:
		return vk::ImageLayout::eUndefined;
	case Ping::ImageLayout::ColorAttachmentOptimal:
		return vk::ImageLayout::eColorAttachmentOptimal;
	case Ping::ImageLayout::PresentSource:
		return vk::ImageLayout::ePresentSrcKHR;
	case Ping::ImageLayout::DepthAttachmentOptimal:
		return vk::ImageLayout::eDepthAttachmentOptimal;
	}
	throw std::runtime_error("Unhandled Ping::ImageLayout");
}

vk::ImageAspectFlags Backend::ToVulkan(Ping::ImageAspect aspect)
{
	vk::ImageAspectFlags result{};
	if (Ping::HasFlag(aspect, Ping::ImageAspect::Color))
		result |= vk::ImageAspectFlagBits::eColor;
	if (Ping::HasFlag(aspect, Ping::ImageAspect::Depth))
		result |= vk::ImageAspectFlagBits::eDepth;
	return result;
}

vk::AccessFlags2 Backend::ToVulkan(Ping::AccessMask mask)
{
	vk::AccessFlags2 result{};
	if (Ping::HasFlag(mask, Ping::AccessMask::ColorAttachmentWrite))
		result |= vk::AccessFlagBits2::eColorAttachmentWrite;
	if (Ping::HasFlag(mask, Ping::AccessMask::DepthStencilAttachmentWrite))
		result |= vk::AccessFlagBits2::eDepthStencilAttachmentWrite;
	return result;
}

vk::PipelineStageFlags2 Backend::ToVulkan(Ping::PipelineStage stage)
{
	vk::PipelineStageFlags2 result{};
	if (Ping::HasFlag(stage, Ping::PipelineStage::ColorAttachmentOutput))
		result |= vk::PipelineStageFlagBits2::eColorAttachmentOutput;
	if (Ping::HasFlag(stage, Ping::PipelineStage::BottomOfPipe))
		result |= vk::PipelineStageFlagBits2::eBottomOfPipe;
	if (Ping::HasFlag(stage, Ping::PipelineStage::EarlyFragmentTests))
		result |= vk::PipelineStageFlagBits2::eEarlyFragmentTests;
	if (Ping::HasFlag(stage, Ping::PipelineStage::LateFragmentTests))
		result |= vk::PipelineStageFlagBits2::eLateFragmentTests;
	return result;
}

vk::BufferUsageFlags Backend::ToVulkan(Ping::BufferUsage usage)
{
	vk::BufferUsageFlags result{};
	if (Ping::HasFlag(usage, Ping::BufferUsage::TransferDst))
		result |= vk::BufferUsageFlagBits::eTransferDst;
	if (Ping::HasFlag(usage, Ping::BufferUsage::TransferSrc))
		result |= vk::BufferUsageFlagBits::eTransferSrc;
	if (Ping::HasFlag(usage, Ping::BufferUsage::VertexBuffer))
		result |= vk::BufferUsageFlagBits::eVertexBuffer;
	if (Ping::HasFlag(usage, Ping::BufferUsage::IndexBuffer))
		result |= vk::BufferUsageFlagBits::eIndexBuffer;
	if (Ping::HasFlag(usage, Ping::BufferUsage::UniformBuffer))
		result |= vk::BufferUsageFlagBits::eUniformBuffer;
	if (Ping::HasFlag(usage, Ping::BufferUsage::StorageBuffer))
		result |= vk::BufferUsageFlagBits::eStorageBuffer;
	return result;
}

vk::CommandBufferUsageFlags Backend::ToVulkan(Ping::CommandBufferUsage usage)
{
	vk::CommandBufferUsageFlags result{};
	if (Ping::HasFlag(usage, Ping::CommandBufferUsage::OneTimeSubmit))
		result |= vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
	if (Ping::HasFlag(usage, Ping::CommandBufferUsage::RenderPassContinue))
		result |= vk::CommandBufferUsageFlagBits::eRenderPassContinue;
	if (Ping::HasFlag(usage, Ping::CommandBufferUsage::SimultaneousUse))
		result |= vk::CommandBufferUsageFlagBits::eSimultaneousUse;
	return result;
}

vk::MemoryPropertyFlags Backend::ToVulkan(Ping::MemoryProperty property)
{
	vk::MemoryPropertyFlags result{};
	if (Ping::HasFlag(property, Ping::MemoryProperty::DeviceLocal))
		result |= vk::MemoryPropertyFlagBits::eDeviceLocal;
	if (Ping::HasFlag(property, Ping::MemoryProperty::HostVisible))
		result |= vk::MemoryPropertyFlagBits::eHostVisible;
	if (Ping::HasFlag(property, Ping::MemoryProperty::HostCoherent))
		result |= vk::MemoryPropertyFlagBits::eHostCoherent;
	return result;
}

vk::Format Backend::ToVulkan(Ping::VertexFormat format)
{
	switch (format)
	{
	case Ping::VertexFormat::Float32x2:
		return vk::Format::eR32G32Sfloat;
	case Ping::VertexFormat::Float32x3:
		return vk::Format::eR32G32B32Sfloat;
	case Ping::VertexFormat::Float32x4:
		return vk::Format::eR32G32B32A32Sfloat;
	}
	throw std::runtime_error("Unhandled Ping::VertexFormat");
}

vk::Format Backend::ToVulkan(Ping::Format format)
{
	switch (format)
	{
	case Ping::Format::Undefined:
		return vk::Format::eUndefined;

	case Ping::Format::R8Unorm:
		return vk::Format::eR8Unorm;
	case Ping::Format::R8G8Unorm:
		return vk::Format::eR8G8Unorm;
	case Ping::Format::R8G8B8A8Unorm:
		return vk::Format::eR8G8B8A8Unorm;
	case Ping::Format::R8G8B8A8Srgb:
		return vk::Format::eR8G8B8A8Srgb;
	case Ping::Format::B8G8R8A8Unorm:
		return vk::Format::eB8G8R8A8Unorm;
	case Ping::Format::B8G8R8A8Srgb:
		return vk::Format::eB8G8R8A8Srgb;

	case Ping::Format::A2B10G10R10UnormPack32:
		return vk::Format::eA2B10G10R10UnormPack32;
	case Ping::Format::A2R10G10B10UnormPack32:
		return vk::Format::eA2R10G10B10UnormPack32;

	case Ping::Format::R16Unorm:
		return vk::Format::eR16Unorm;
	case Ping::Format::R16G16Unorm:
		return vk::Format::eR16G16Unorm;
	case Ping::Format::R16G16B16A16Unorm:
		return vk::Format::eR16G16B16A16Unorm;

	case Ping::Format::R16Sfloat:
		return vk::Format::eR16Sfloat;
	case Ping::Format::R16G16Sfloat:
		return vk::Format::eR16G16Sfloat;
	case Ping::Format::R16G16B16A16Sfloat:
		return vk::Format::eR16G16B16A16Sfloat;
	case Ping::Format::R32Sfloat:
		return vk::Format::eR32Sfloat;
	case Ping::Format::R32G32Sfloat:
		return vk::Format::eR32G32Sfloat;
	case Ping::Format::R32G32B32A32Sfloat:
		return vk::Format::eR32G32B32A32Sfloat;
	case Ping::Format::B10G11R11UfloatPack32:
		return vk::Format::eB10G11R11UfloatPack32;

	case Ping::Format::R8Uint:
		return vk::Format::eR8Uint;
	case Ping::Format::R16Uint:
		return vk::Format::eR16Uint;
	case Ping::Format::R32Uint:
		return vk::Format::eR32Uint;

	case Ping::Format::D16Unorm:
		return vk::Format::eD16Unorm;
	case Ping::Format::D32Sfloat:
		return vk::Format::eD32Sfloat;
	case Ping::Format::S8Uint:
		return vk::Format::eS8Uint;
	case Ping::Format::D24UnormS8Uint:
		return vk::Format::eD24UnormS8Uint;
	case Ping::Format::D32SfloatS8Uint:
		return vk::Format::eD32SfloatS8Uint;
	}
	throw std::runtime_error("Unhandled Ping::Format");
}

std::optional<Ping::Format> Backend::TryToPing(vk::Format format)
{
	switch (format)
	{
	case vk::Format::eUndefined:
		return Ping::Format::Undefined;

	case vk::Format::eR8Unorm:
		return Ping::Format::R8Unorm;
	case vk::Format::eR8G8Unorm:
		return Ping::Format::R8G8Unorm;
	case vk::Format::eR8G8B8A8Unorm:
		return Ping::Format::R8G8B8A8Unorm;
	case vk::Format::eR8G8B8A8Srgb:
		return Ping::Format::R8G8B8A8Srgb;
	case vk::Format::eB8G8R8A8Unorm:
		return Ping::Format::B8G8R8A8Unorm;
	case vk::Format::eB8G8R8A8Srgb:
		return Ping::Format::B8G8R8A8Srgb;

	case vk::Format::eA2B10G10R10UnormPack32:
		return Ping::Format::A2B10G10R10UnormPack32;
	case vk::Format::eA2R10G10B10UnormPack32:
		return Ping::Format::A2R10G10B10UnormPack32;

	case vk::Format::eR16Unorm:
		return Ping::Format::R16Unorm;
	case vk::Format::eR16G16Unorm:
		return Ping::Format::R16G16Unorm;
	case vk::Format::eR16G16B16A16Unorm:
		return Ping::Format::R16G16B16A16Unorm;

	case vk::Format::eR16Sfloat:
		return Ping::Format::R16Sfloat;
	case vk::Format::eR16G16Sfloat:
		return Ping::Format::R16G16Sfloat;
	case vk::Format::eR16G16B16A16Sfloat:
		return Ping::Format::R16G16B16A16Sfloat;
	case vk::Format::eR32Sfloat:
		return Ping::Format::R32Sfloat;
	case vk::Format::eR32G32Sfloat:
		return Ping::Format::R32G32Sfloat;
	case vk::Format::eR32G32B32A32Sfloat:
		return Ping::Format::R32G32B32A32Sfloat;
	case vk::Format::eB10G11R11UfloatPack32:
		return Ping::Format::B10G11R11UfloatPack32;

	case vk::Format::eR8Uint:
		return Ping::Format::R8Uint;
	case vk::Format::eR16Uint:
		return Ping::Format::R16Uint;
	case vk::Format::eR32Uint:
		return Ping::Format::R32Uint;

	case vk::Format::eD16Unorm:
		return Ping::Format::D16Unorm;
	case vk::Format::eD32Sfloat:
		return Ping::Format::D32Sfloat;
	case vk::Format::eS8Uint:
		return Ping::Format::S8Uint;
	case vk::Format::eD24UnormS8Uint:
		return Ping::Format::D24UnormS8Uint;
	case vk::Format::eD32SfloatS8Uint:
		return Ping::Format::D32SfloatS8Uint;

	default:
		return std::nullopt;
	}
}

Ping::Format Backend::ToPing(vk::Format format)
{
	if (const std::optional<Ping::Format> mapped = TryToPing(format))
	{
		return *mapped;
	}
	throw std::runtime_error("vk::Format has no Ping::Format mapping: " + vk::to_string(format));
}

vk::ShaderStageFlags Backend::ToVulkan(Ping::ShaderStage stage)
{
	vk::ShaderStageFlags result{};
	if (Ping::HasFlag(stage, Ping::ShaderStage::Vertex))
		result |= vk::ShaderStageFlagBits::eVertex;
	if (Ping::HasFlag(stage, Ping::ShaderStage::Fragment))
		result |= vk::ShaderStageFlagBits::eFragment;
	return result;
}

vk::DescriptorType Backend::ToVulkan(Ping::DescriptorType type)
{
	switch (type)
	{
	case Ping::DescriptorType::UniformBuffer:
		return vk::DescriptorType::eUniformBuffer;
	case Ping::DescriptorType::CombinedImageSampler:
		return vk::DescriptorType::eCombinedImageSampler;
	case Ping::DescriptorType::StorageBuffer:
		return vk::DescriptorType::eStorageBuffer;
	}
	throw std::runtime_error("Unhandled Ping::DescriptorType");
}

vk::ImageUsageFlags Backend::ToVulkan(Ping::ImageUsage usage)
{
	vk::ImageUsageFlags result{};
	if (Ping::HasFlag(usage, Ping::ImageUsage::Sampled))
		result |= vk::ImageUsageFlagBits::eSampled;
	return result;
}

vk::Filter Backend::ToVulkan(Ping::SamplerFilterMode filter)
{
	switch (filter)
	{
	case Ping::SamplerFilterMode::Linear:
		return vk::Filter::eLinear;
	case Ping::SamplerFilterMode::Nearest:
		return vk::Filter::eNearest;
	}
	throw std::runtime_error("Unhandled Ping::SamplerFilterMode");
}

vk::SamplerMipmapMode Backend::ToVulkan(Ping::SamplerMipMapMode mipmap_mode)
{
	switch (mipmap_mode)
	{
	case Ping::SamplerMipMapMode::Linear:
		return vk::SamplerMipmapMode::eLinear;
	case Ping::SamplerMipMapMode::Nearest:
		return vk::SamplerMipmapMode::eNearest;
	}
	throw std::runtime_error("Unhandled Ping::SamplerMipMapMode");
}

vk::SamplerAddressMode Backend::ToVulkan(Ping::SamplerAddressMode address_mode)
{
	switch (address_mode)
	{
	case Ping::SamplerAddressMode::Repeat:
		return vk::SamplerAddressMode::eRepeat;
	case Ping::SamplerAddressMode::MirroredRepeat:
		return vk::SamplerAddressMode::eMirroredRepeat;
	case Ping::SamplerAddressMode::ClampToEdge:
		return vk::SamplerAddressMode::eClampToEdge;
	case Ping::SamplerAddressMode::MirrorClampToEdge:
		return vk::SamplerAddressMode::eMirrorClampToEdge;
	case Ping::SamplerAddressMode::ClampToBorder:
		return vk::SamplerAddressMode::eClampToBorder;
	}
	throw std::runtime_error("Unhandled Ping::SamplerAddressMode");
}


vk::CullModeFlags Backend::ToVulkan(Ping::CullMode cull_mode)
{
	vk::CullModeFlags result{};
	if (Ping::HasFlag(cull_mode, Ping::CullMode::Front))
		result |= vk::CullModeFlagBits::eFront;
	if (Ping::HasFlag(cull_mode, Ping::CullMode::Back))
		result |= vk::CullModeFlagBits::eBack;
	if (Ping::HasFlag(cull_mode, Ping::CullMode::FrontAndBack))
		result |= vk::CullModeFlagBits::eFrontAndBack;
	return result;
}

vk::BlendFactor Backend::ToVulkan(Ping::BlendFactor blend_factor)
{
	switch (blend_factor)
	{
	case Ping::BlendFactor::Zero:
		return vk::BlendFactor::eZero;
	case Ping::BlendFactor::One:
		return vk::BlendFactor::eOne;
	case Ping::BlendFactor::SrcAlpha:
		return vk::BlendFactor::eSrcAlpha;
	case Ping::BlendFactor::OneMinusSrcAlpha:
		return vk::BlendFactor::eOneMinusSrcAlpha;
	case Ping::BlendFactor::DstAlpha:
		return vk::BlendFactor::eDstAlpha;
	case Ping::BlendFactor::OneMinusDstAlpha:
		return vk::BlendFactor::eOneMinusDstAlpha;
	}
	throw std::runtime_error("Unhandled Ping::BlendFactor");
}
